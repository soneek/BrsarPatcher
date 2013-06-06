echo off
SET /P folder=What folder are your BRSTMs in? 
SET /P brsar=Enter the filename of your brsar, minus the .brsar piece. 
copy %brsar%.brsar %brsar%.brsar.backup
for %%i IN (%folder%/*.brstm) DO universalbrsarpatcher %brsar%.brsar %folder%/%%i 