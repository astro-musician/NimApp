# installer.nsi
Outfile "NimNN-installer.exe"
InstallDir $PROGRAMFILES\NimNN
Page directory
Page instfiles

Section "Install"
    SetOutPath $INSTDIR
    File "build\Release\NimNN.exe"
    CreateShortCut "$DESKTOP\NimNN.lnk" "$INSTDIR\NimNN.exe"
SectionEnd