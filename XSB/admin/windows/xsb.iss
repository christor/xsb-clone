; Script generated by the Inno Setup Script Wizard.

#define MyAppName "XSB"
#define MyAppVerName "XSB 3.2"
#define MyAppPublisher "XSB"
#define MyAppURL "http://xsb.sourceforge.net/"
#define MyAppUrlName "XSB Web Site.url"

#define XSB_DIR "{reg:HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment,XSB_DIR|{pf}\XSB}"
#define MyBaseDir "C:\lgtsvn"

[Setup]
AppName={#MyAppName}
AppVerName={#MyAppVerName}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
ChangesEnvironment=yes
DefaultDirName={#XSB_DIR}
DefaultGroupName={#MyAppName}
DisableProgramGroupPage=yes
LicenseFile={#MyBaseDir}\LICENSE
InfoBeforeFile={#MyBaseDir}\README
OutputBaseFilename=xsb-3.2
Compression=lzma
SolidCompression=yes
PrivilegesRequired=none

VersionInfoVersion=3.2
VersionInfoCopyright=� The Research Foundation of SUNY, 1986, 1993-2002

AllowRootDirectory=yes
UninstallFilesDir="{userdocs}\XSB uninstaller"

MinVersion=0,5.0

[Types]
Name: "full"; Description: "Full XSB installation (recommended)"
Name: "base"; Description: "Base XSB installation"
Name: "custom"; Description: "Custom XSB installation"; Flags: iscustom

[Components]
Name: "base"; Description: "Base system"; Types: full base custom; Flags: disablenouninstallwarning
Name: "base\sources"; Description: "Base system plus Prolog source files"; Types: full base custom; Flags: disablenouninstallwarning
Name: "documentation"; Description: "Documentation"; Types: full custom; Flags: disablenouninstallwarning
Name: "examples"; Description: "Examples"; Types: full custom; Flags: disablenouninstallwarning
Name: "packages"; Description: "Packages"; Types: full custom; Flags: disablenouninstallwarning

[Tasks]
Name: website; Description: "&Visit {#MyAppName} web site"; Components: base
Name: shortcut; Description: "&Create a desktop shortcut to the XSB folder"; Components: base

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Messages]
BeveledLabel=XSB 3.2 � The Research Foundation of SUNY, 1986, 1993-2002

[Dirs]
Name: "{userdocs}\XSB uninstaller"

[Files]
Source: "{#MyBaseDir}\*"; Excludes: ".*,CVS"; DestDir: "{app}"; Components: base; Flags: ignoreversion recursesubdirs createallsubdirs

Source: "{#MyBaseDir}\bin\*"; Excludes: ".*,CVS"; DestDir: "{app}"; Components: base; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#MyBaseDir}\config\*"; Excludes: ".*,CVS"; DestDir: "{app}"; Components: base; Flags: ignoreversion recursesubdirs createallsubdirs

Source: "{#MyBaseDir}\syslib\*.xwam"; Excludes: ".*,CVS"; DestDir: "{app}"; Components: base; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#MyBaseDir}\cmplib\*.xwam"; Excludes: ".*,CVS"; DestDir: "{app}"; Components: base; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#MyBaseDir}\lib\*.xwam"; Excludes: ".*,CVS"; DestDir: "{app}"; Components: base; Flags: ignoreversion recursesubdirs createallsubdirs

Source: "{#MyBaseDir}\syslib\*"; Excludes: ".*,CVS"; DestDir: "{app}"; Components: base\sources; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#MyBaseDir}\cmplib\*"; Excludes: ".*,CVS"; DestDir: "{app}"; Components: base\sources; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#MyBaseDir}\lib\*"; Excludes: ".*,CVS"; DestDir: "{app}"; Components: base\sources; Flags: ignoreversion recursesubdirs createallsubdirs

Source: "{#MyBaseDir}\docs\*"; Excludes: ".*,CVS"; DestDir: "{app}"; Components: documentation; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#MyBaseDir}\examples\*"; Excludes: ".*,CVS"; DestDir: "{app}"; Components: examples; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#MyBaseDir}\packages\*"; Excludes: ".*,CVS"; DestDir: "{app}"; Components: packages; Flags: ignoreversion recursesubdirs createallsubdirs

[INI]
Filename: "{app}\{#MyAppUrlName}"; Section: "InternetShortcut"; Key: "URL"; String: "{#MyAppURL}"; Components: base

[Icons]
Name: "{group}\XSB"; Filename: "{app}\config\x86-pc-windows\bin\xsb.exe"; Parameters: ""; Comment: "Runs XSB within a command shell"; WorkingDir: "{userdocs}"; Components: base; Flags: createonlyiffileexists

Name: "{group}\License"; Filename: "{app}\LICENSE"; Components: base
Name: "{group}\Read Me"; Filename: "{app}\README"; Components: base

Name: "{group}\Web Site"; Filename: "{#MyAppUrl}"; Components: base

Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"; Components: base

Name: "{userdesktop}\XSB"; Filename: "{app}"; Components: base; Tasks: shortcut

[Registry]
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType: expandsz; ValueName: "XSB_DIR"; ValueData: "{app}"; Components: base; Flags: deletevalue uninsdeletevalue

[Run]
Filename: "{app}\{#MyAppUrlName}"; Flags: shellexec nowait; Tasks: website

[UninstallDelete]
Type: filesandordirs; Name: "{app}"; Components: base
Type: filesandordirs; Name: "{group}"; Components: base
