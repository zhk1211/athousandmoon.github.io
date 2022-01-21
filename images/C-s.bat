echo off & color 0A
set DIR="%cd%"
echo DIR=%DIR%

for /R %%f in (*.jpg) do ( 
echo %%f
)
pause
