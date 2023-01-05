
#define MyAppName "Mia's Desktop"
#define MyAppVersion "0.1.3-beta"
#define MyAppPublisher "Octetos, Inc."
#define MyAppURL "https://github.com/azaeldevel"
#define MyAppExeName "mias-desk.exe"
#define MyAppAssocName MyAppName + " File"
#define MyAppAssocExt ".mdc"
#define MyAppAssocKey StringChange(MyAppAssocName, " ", "") + MyAppAssocExt

[Setup]
AppId={{EAA4B4AA-18AA-4405-BFFE-0E2C5FF155E7}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
ChangesAssociations=yes
DisableProgramGroupPage=yes
PrivilegesRequiredOverridesAllowed=commandline
OutputBaseFilename=mias-desk-setup
SetupIconFile=C:\Users\Azael\Documents\develop\octetos\mias\mias.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern
OutputDir=installer

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "desk\bin\Debug\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\core\bin\Debug\octetos-core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\db-abstract\bin\Debug\octetos-db-abstract.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\db-maria\bin\Debug\octetos-db-maria.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\muposys\core\bin\Debug\muposys-core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\muposys\desk\bin\Debug\muposys-desk.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\mias\core\bin\Debug\mias-core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\mias\desk\bin\Debug\mias-desk.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\mias\desk\bin\Debug\mias-desk.exe"; DestDir: "{app}"; Flags: ignoreversion  

Source: "C:\Users\Azael\Documents\develop\octetos\mias\installer\Windows-10-master\gtk-3.20\*"; DestDir: "{app}\share\themes\Windows10\gtk-3.20"; Flags: ignoreversion recursesubdirs 
Source: "C:\msys64\mingw64\share\icons\Adwaita\*"; DestDir: "{app}\share\icons\Adwaita"; Flags: ignoreversion recursesubdirs 
Source: "C:\Users\Azael\Documents\develop\octetos\mias\installer\settings.ini"; DestDir: "{app}\etc\gtk-3.0"; Flags: ignoreversion  

//Source: "C:\msys64\mingw64\bin\libsigc-2.0-0.dll"; DestDir: "{app}"; Flags: ignoreversion    
//Source: "C:\msys64\mingw64\bin\libgdk-3-0.dll"; DestDir: "{app}"; Flags: ignoreversion             
//Source: "C:\msys64\mingw64\bin\libcairo-2.dll"; DestDir: "{app}"; Flags: ignoreversion
//Source: "C:\msys64\mingw64\bin\libcairo-gobject-2.dll"; DestDir: "{app}"; Flags: ignoreversion
//Source: "C:\msys64\mingw64\bin\libgtk-3-0.dll"; DestDir: "{app}"; Flags: ignoreversion

//Source: "C:\msys64\mingw64\bin\libgcc_s_seh-1.dll"; DestDir: "{app}"; Flags: ignoreversion   
//Source: "C:\msys64\mingw64\bin\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion    
//Source: "C:\msys64\mingw64\bin\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion
//Source: "C:\msys64\mingw64\bin\libintl-8.dll"; DestDir: "{app}"; Flags: ignoreversion       
//Source: "C:\msys64\mingw64\bin\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion       
//Source: "C:\msys64\mingw64\bin\libmariadb.dll"; DestDir: "{app}"; Flags: ignoreversion  

//Source: "C:\msys64\mingw64\bin\libgtkmm-3.0-1.dll"; DestDir: "{app}"; Flags: ignoreversion   
//Source: "C:\msys64\mingw64\bin\libgdkmm-3.0-1.dll"; DestDir: "{app}"; Flags: ignoreversion  
//Source: "C:\msys64\mingw64\bin\libatkmm-1.6-1.dll"; DestDir: "{app}"; Flags: ignoreversion   
//Source: "C:\msys64\mingw64\bin\libglibmm-2.4-1.dll"; DestDir: "{app}"; Flags: ignoreversion    
//Source: "C:\msys64\mingw64\bin\libcairomm-1.0-1.dll"; DestDir: "{app}"; Flags: ignoreversion     
//Source: "C:\msys64\mingw64\bin\libgiomm-2.4-1.dll"; DestDir: "{app}"; Flags: ignoreversion
//Source: "C:\msys64\mingw64\bin\libconfig++-11.dll"; DestDir: "{app}"; Flags: ignoreversion  
//Source: "C:\msys64\mingw64\bin\libpangomm-1.4-1.dll"; DestDir: "{app}"; Flags: ignoreversion   
//Source: "C:\msys64\mingw64\bin\libpangowin32-1.0-0.dll"; DestDir: "{app}"; Flags: ignoreversion

[Registry]
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocExt}\OpenWithProgids"; ValueType: string; ValueName: "{#MyAppAssocKey}"; ValueData: ""; Flags: uninsdeletevalue
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}"; ValueType: string; ValueName: ""; ValueData: "{#MyAppAssocName}"; Flags: uninsdeletekey
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\{#MyAppExeName},0"
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\{#MyAppExeName}"" ""%1"""
Root: HKA; Subkey: "Software\Classes\Applications\{#MyAppExeName}\SupportedTypes"; ValueType: string; ValueName: ".myp"; ValueData: ""

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "C:\msys64\mingw64\bin\glib-compile-schemas.exe"; Description: "Generando configuración de Gtk."; Parameters: "share/glib-2.0/schemas"
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

