# Per-file syntax-only (/c, no link) MSVC 7.10 compile check over every
# raw-ported .c file, mirroring the Makefile's `winelib-syntax-check` target
# but using the real compiler instead of winegcc. Writes a summary and a
# per-file error log to tools/msvc_syntax_check_results.txt.
$root = "Z:\Developer\GunBound-Decomp\tools\msvc-env\msvc7"
$env:INCLUDE = "$root\include;$root\PlatformSDK\include"
$env:LIB = "$root\lib;$root\PlatformSDK\lib"
$cl = "$root\bin\cl.exe"

Set-Location Z:\Developer\GunBound-Decomp
$files = Get-ChildItem -Recurse -Path src -Filter *.c |
    Where-Object { $_.FullName -notmatch '\\lzhuf\\' -and $_.FullName -notmatch '\\msvc_crt_atl\\' -and $_.Name -ne 'test_lzhuf.c' }

$results = @()
$i = 0
foreach ($f in $files) {
    $i++
    $rel = $f.FullName.Substring((Get-Location).Path.Length + 1)
    $out = & $cl /c /nologo /I include\msvc /I include /Zs $rel 2>&1
    $errors = $out | Select-String ": error " | ForEach-Object { $_.ToString() }
    $ok = ($errors.Count -eq 0)
    $results += [PSCustomObject]@{ File = $rel; Ok = $ok; FirstError = if ($errors) { $errors[0] } else { "" } }
    if ($i % 200 -eq 0) { Write-Host "...$i/$($files.Count)" }
}

$results | Export-Csv -NoTypeInformation -Path tools\msvc_syntax_check_results.csv
$okCount = ($results | Where-Object Ok).Count
Write-Host "OK: $okCount / $($results.Count)"
$results | Where-Object { -not $_.Ok } | Group-Object { $_.FirstError -replace '^.*error (C\d+):.*$', '$1' } |
    Sort-Object Count -Descending | Select-Object Count, Name | Format-Table -AutoSize
