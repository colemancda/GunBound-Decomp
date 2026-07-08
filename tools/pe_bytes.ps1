# Minimal PE VA->file-offset byte dumper (no dumpbin/objdump needed).
# Usage: pe_bytes.ps1 <path-to-pe> <VA-hex> <length-decimal>
param(
    [Parameter(Mandatory=$true)][string]$Path,
    [Parameter(Mandatory=$true)][string]$VaHex,
    [Parameter(Mandatory=$true)][int]$Length
)

$va = [Convert]::ToUInt32($VaHex, 16)
$bytes = [System.IO.File]::ReadAllBytes($Path)

$e_lfanew = [BitConverter]::ToInt32($bytes, 0x3C)
$peOff = $e_lfanew
if ([System.Text.Encoding]::ASCII.GetString($bytes, $peOff, 4) -ne "PE`0`0") {
    throw "Not a PE file (or bad e_lfanew)"
}
$coffOff = $peOff + 4
$numSections = [BitConverter]::ToUInt16($bytes, $coffOff + 2)
$optHeaderSize = [BitConverter]::ToUInt16($bytes, $coffOff + 16)
$optHeaderOff = $coffOff + 20
$imageBase = [BitConverter]::ToUInt32($bytes, $optHeaderOff + 28)

$sectionTableOff = $optHeaderOff + $optHeaderSize
$rva = $va - $imageBase

$found = $false
for ($i = 0; $i -lt $numSections; $i++) {
    $secOff = $sectionTableOff + ($i * 40)
    $name = [System.Text.Encoding]::ASCII.GetString($bytes, $secOff, 8).TrimEnd([char]0)
    $virtSize = [BitConverter]::ToUInt32($bytes, $secOff + 8)
    $virtAddr = [BitConverter]::ToUInt32($bytes, $secOff + 12)
    $rawSize = [BitConverter]::ToUInt32($bytes, $secOff + 16)
    $rawPtr = [BitConverter]::ToUInt32($bytes, $secOff + 20)

    if ($rva -ge $virtAddr -and $rva -lt ($virtAddr + [Math]::Max($virtSize, $rawSize))) {
        $fileOff = $rawPtr + ($rva - $virtAddr)
        Write-Host "Section: $name  ImageBase: 0x$($imageBase.ToString('X'))  RVA: 0x$($rva.ToString('X'))  FileOffset: 0x$($fileOff.ToString('X'))"
        $slice = $bytes[$fileOff..($fileOff + $Length - 1)]
        $hex = ($slice | ForEach-Object { $_.ToString('X2') }) -join ' '
        Write-Host $hex
        $found = $true
        break
    }
}
if (-not $found) { throw "VA 0x$($va.ToString('X')) not found in any section" }
