# Minimal COFF .obj parser: list text-section symbols with offsets/sizes,
# or dump raw bytes for one named function. Good enough for eyeballing a
# single non-COMDAT-split .text section from old MSVC (no /Gy).
param(
    [Parameter(Mandatory=$true)][string]$Path,
    [string]$FuncName
)

$bytes = [System.IO.File]::ReadAllBytes($Path)

$numSections = [BitConverter]::ToUInt16($bytes, 2)
$symTabOff   = [BitConverter]::ToUInt32($bytes, 8)
$numSymbols  = [BitConverter]::ToUInt32($bytes, 12)

$sectionTableOff = 20
$sections = @()
for ($i = 0; $i -lt $numSections; $i++) {
    $off = $sectionTableOff + ($i * 40)
    $name = [System.Text.Encoding]::ASCII.GetString($bytes, $off, 8).TrimEnd([char]0)
    $rawSize = [BitConverter]::ToUInt32($bytes, $off + 16)
    $rawPtr  = [BitConverter]::ToUInt32($bytes, $off + 20)
    $sections += [PSCustomObject]@{ Index = $i+1; Name = $name; RawSize = $rawSize; RawPtr = $rawPtr }
}

# String table follows symbol table: symTabOff + numSymbols*18
$strTabOff = $symTabOff + ($numSymbols * 18)

function Get-SymName($symOff) {
    $zeroes = [BitConverter]::ToUInt32($bytes, $symOff)
    if ($zeroes -eq 0) {
        $strOff = [BitConverter]::ToUInt32($bytes, $symOff + 4)
        $absOff = $strTabOff + $strOff
        $len = 0
        while ($bytes[$absOff + $len] -ne 0) { $len++ }
        return [System.Text.Encoding]::ASCII.GetString($bytes, $absOff, $len)
    } else {
        return [System.Text.Encoding]::ASCII.GetString($bytes, $symOff, 8).TrimEnd([char]0)
    }
}

$syms = @()
$i = 0
while ($i -lt $numSymbols) {
    $symOff = $symTabOff + ($i * 18)
    $name = Get-SymName $symOff
    $value = [BitConverter]::ToUInt32($bytes, $symOff + 8)
    $secNum = [BitConverter]::ToInt16($bytes, $symOff + 12)
    $type = [BitConverter]::ToUInt16($bytes, $symOff + 14)
    $storageClass = $bytes[$symOff + 16]
    $numAux = $bytes[$symOff + 17]
    if ($secNum -gt 0 -and ($type -eq 0x20 -or $storageClass -eq 2)) {
        $syms += [PSCustomObject]@{ Name = $name; Section = $secNum; Offset = $value; StorageClass = $storageClass }
    }
    $i += 1 + $numAux
}

if (-not $FuncName) {
    $syms | Where-Object { $_.StorageClass -eq 2 } | Sort-Object Section, Offset | Format-Table -AutoSize
    "--- sections ---"
    $sections | Format-Table -AutoSize
    return
}

$target = $syms | Where-Object { $_.Name -eq $FuncName } | Select-Object -First 1
if (-not $target) { throw "Symbol '$FuncName' not found" }

$funcSyms = $syms | Where-Object { $_.Section -eq $target.Section } | Sort-Object Offset
$idx = [array]::IndexOf($funcSyms.Name, $target.Name)
$startOff = $target.Offset
$endOff = if ($idx -lt $funcSyms.Count - 1) { $funcSyms[$idx+1].Offset } else { $null }

$sec = $sections | Where-Object { $_.Index -eq $target.Section }
$fileStart = $sec.RawPtr + $startOff
$fileEnd = if ($endOff) { $sec.RawPtr + $endOff } else { $sec.RawPtr + $sec.RawSize }
$len = $fileEnd - $fileStart

Write-Host "Function: $FuncName  Section: $($sec.Name)  Offset: 0x$($startOff.ToString('X'))  Length: $len"
$slice = $bytes[$fileStart..($fileEnd - 1)]
$hex = ($slice | ForEach-Object { $_.ToString('X2') }) -join ' '
Write-Host $hex
