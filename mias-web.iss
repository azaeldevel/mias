
#define MyAppName "mias"
#define MyAppVersion "0.1.0-alpha"
#define MyAppPublisher "Octetos, Inc."
#define MyAppURL "https://github.com/azaeldevel"
#define MyAppExeName "mias-desk.exe"
#define MyAppAssocName MyAppName + " File"
#define MyAppAssocExt ".mdc"
#define MyAppAssocKey StringChange(MyAppAssocName, " ", "") + MyAppAssocExt

[Setup]
AppId={{965A7609-FBCC-442D-A17C-59FA92850CB4}
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
OutputBaseFilename=mias-web-setup
SetupIconFile=C:\Users\Azael\Documents\develop\octetos\mias\mias.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"

[Files]
Source: "C:\Users\Azael\Documents\develop\octetos\core\bin\Debug\octetos-core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\db-abstract\bin\Debug\octetos-db-abstract.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\db-maria\bin\Debug\octetos-db-maria.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\muposys\core\bin\Debug\muposys-core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\muposys\web\bin\Debug\muposys-web.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\muposys\web\bin\Debug\login.cgi"; DestDir: "{app}"; Flags: ignoreversion   
Source: "C:\Users\Azael\Documents\develop\octetos\muposys\web\html\css\Mkos-Big-Sur\appearance\muposys.css"; DestDir: "{app}\css\Mkos-Big-Sur\appearance\"; Flags: ignoreversion  
Source: "C:\Users\Azael\Documents\develop\octetos\muposys\web\html\css\Mkos-Big-Sur\icons\application.css"; DestDir: "{app}\css\Mkos-Big-Sur\icons\"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\muposys\web\html\css\Mkos-Big-Sur\login.css"; DestDir: "{app}\css\Mkos-Big-Sur\"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\muposys\web\html\css\Mkos-Big-Sur\theme.css"; DestDir: "{app}\css\Mkos-Big-Sur\"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\muposys\web\html\js\*"; DestDir: "{app}\js"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\muposys\web\html\index.html"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\muposys\web\html\login.html"; DestDir: "{app}"; Flags: ignoreversion  
Source: "C:\Users\Azael\Documents\develop\octetos\mias\core\bin\Debug\mias-core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\mias\web\bin\Debug\mias-web.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Azael\Documents\develop\octetos\mias\web\bin\Debug\application.cgi"; DestDir: "{app}"; Flags: ignoreversion

[Registry]
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocExt}\OpenWithProgids"; ValueType: string; ValueName: "{#MyAppAssocKey}"; ValueData: ""; Flags: uninsdeletevalue
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}"; ValueType: string; ValueName: ""; ValueData: "{#MyAppAssocName}"; Flags: uninsdeletekey
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\{#MyAppExeName},0"
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\{#MyAppExeName}"" ""%1"""
Root: HKA; Subkey: "Software\Classes\Applications\{#MyAppExeName}\SupportedTypes"; ValueType: string; ValueName: ".myp"; ValueData: ""
