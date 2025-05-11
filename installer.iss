[Setup]
AppName=Truco Tricks
AppVersion=@VERSION@
DefaultDirName={autopf}\Truco Tricks
OutputDir=.
OutputBaseFilename= trucotricks-windows-@VERSION@-setup
SetupIconFile=icon.ico
WizardImageFile=finish_wizard.bmp
LicenseFile=COPYING

[Icons]
Name: "{commondesktop}\Truco Tricks"; Filename: "{app}\trucotricks.exe"; Tasks: desktopicon
Name: "{group}\Truco Tricks"; Filename: "{app}\trucotricks.exe"

[Tasks]
Name: "desktopicon"; Description: "Create &desktop icon"; Flags: unchecked

[Run]
Filename: "{app}\trucotricks.exe"; Description: "Launch Truco Tricks"; Flags: nowait postinstall skipifsilent

[Files]
Source: "trucotricks-windows-@VERSION@\trucotricks.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "trucotricks-windows-@VERSION@\glfw3.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "trucotricks-windows-@VERSION@\libnanovg.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "trucotricks-windows-@VERSION@\opengl32.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "trucotricks-windows-@VERSION@\SDL2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "trucotricks-windows-@VERSION@\SDL2_mixer.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "trucotricks-windows-@VERSION@\resources\*"; DestDir: "{app}\resources"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "COPYING"; DestDir: "{app}"; Flags: ignoreversion
