@echo off
for /R %%F in (*.cpp *.h) do (
    "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\Llvm\bin\clang-format.exe" -i "%%F"
)
echo Formatting complete!
pause