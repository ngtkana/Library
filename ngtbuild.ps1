# ----------------------------------------------
# build .vocode/cpp.code-snippets
# ----------------------------------------------

function ngtwrite {
  param (
    $instr
  , $tabs
  )
  $outstr = ""
  for ($i = 0; $i -lt $tabs; $i++) {
    $outstr += "`t"
  }
  $outstr += $instr
  Write-Output $outstr
}
function escape_and_quote {
  param (
    $instr
    , $tabs
    , $final
  )
  $instr = $instr.replace("  ", "`t")
  $instr = $instr.replace("`t", "`\t")
  $instr = $instr.replace("`n", "`\n")
  $instr = $instr.replace("`"", "`\`"")
  $outstr = "`""
  $outstr += $instr
  $outstr += "`""
  if (($final -eq $false)) { $outstr += "," }
  ngtwrite $outstr $tabs
}
function parse {
  param (
    $infile
  )
  $snippet_name = [System.IO.Path]::GetFileNameWithoutExtension($infile.Name).replace("_", " ")
  ngtwrite "`"$snippet_name`": {" 1
  ngtwrite "`"prefix`": `"$snippet_name`"," 2
  ngtwrite "`"body`": [" 2
  $stream = New-Object System.IO.StreamReader($infile.FullName)
  $flg = $false
  $line = ""
  while (($nxtline = $stream.ReadLine()) -ne $null) {
    if (($flg -eq $true)) {
      escape_and_quote $line 3 (($nxtline -eq "// end"))
    }
    if (($line -eq "// begin")) { $flg = $true }
    if (($nxtline -eq "// end")) { $flg = $false }
    $line = $nxtline
  }
  $stream.Close()
  ngtwrite "]," 2
  ngtwrite "`"description`": `"none`"" 2
  ngtwrite "}," 1
}

$snippets = "./.vscode/cpp.code-snippets"
Clear-Content $snippets

ngtwrite "{" | Add-Content $snippets

Get-ChildItem -Recurse -Path library/*.cpp | ForEach-Object {
  parse $_ | Add-Content $snippets
}

# Get-ChildItem -Path library/fragments/*.json | ForEach-Object {
#   Get-Content -Encoding UTF8 $_.FullName | Add-Content -Encoding UTF8 $snippets
# }

ngtwrite "}" 0 | Add-Content $snippets


Get-ChildItem -Recurse -Path library/*.cpp | ForEach-Object {
  New-Item -Force -Path reference -Name "$($_.Name).md"
}



# ----------------------------------------------
# build index.md
# ----------------------------------------------

function make_link {
  param (
    $infile
  )
  $outstr = "- ["
  $outstr += [System.IO.Path]::GetFileNameWithoutExtension($infile.Name).replace("_", " ")
  $outstr += "]("
  $outstr += (Resolve-Path $infile.fullname-Relative).remove(0, 1)
  $outstr += ")"
  $outstr | Add-Content readme
}

$readme = "readme.md"
Clear-Content readme

"# Library" | Add-Content readme

Get-ChildItem -Recurse -Path library/*.cpp | ForEach-Object {
  make_link $_
}
"" | Add-Content readme

"# How to use script" | Add-Content -Encoding UTF8 readme
Get-Content -Encoding UTF8 -Path markdown/script.md | Add-Content -Encoding UTF8 readme


