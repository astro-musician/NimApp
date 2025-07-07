# installer.nsi
Outfile "NimNN-installer.exe"
InstallDir $PROGRAMFILES\NimNN
Page directory
Page instfiles

Section "Install"
    SetOutPath $INSTDIR
    File /r "dist\*.*"
    CreateShortCut "$DESKTOP\NimNN.lnk" "$INSTDIR\NimNN.exe"
SectionEnd

Section "Uninstall"
    Delete $INSTDIR\NImNN.exe
    Delete $DESKTOP\NimNN.lnk
    RMDir /r "$INSTDIR"
SectionEnd