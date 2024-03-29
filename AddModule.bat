@ECHO off

:START

SETLOCAL EnableDelayedExpansion
SET /P moduleType="Enter Module type (0 = Engine, 1 = Editor, 2 = Test, 3 = Project): "
IF NOT DEFINED moduleType (
	ECHO Module type is not defined 
	GOTO :end
)

ECHO Create files for module type: !moduleType!
SET "modulesPath="

IF !moduleType!==0 (
	SET modulesPath=%~dp0Protostar-Engine\Source\Modules\
) 
IF !moduleType!==1 (
	SET modulesPath=%~dp0Protostar-Editor\Source\Modules\
)
IF !moduleType!==2 (
	SET modulesPath=%~dp0Protostar-Engine-Test\Source\Modules\
)

IF !moduleType!==3 (
	::implement project based modules
	ECHO Project based modules are currently not implemented.
	GOTO :end
)

SET /A checkRange=0
IF !moduleType! GEQ 4 SET /A checkRange=1
IF !moduleType! LSS 0  SET /A checkRange=1

IF !checkRange!==1 (
	ECHO Module type !moduleType! not supported.
	GOTO :end
)

SET /A moduleAlreadyCreated=0

SET modulePath=

IF !moduleType!==1 (
	SET /P setEditorBaseModule="Do you want to create a base module for the editor?(Y/N)"
	IF !setEditorBaseModule!==Y (
		SET sharpmakeFilePath=!modulesPath!\Protostar.Editor.Sharpmake.cs
		SET /A sharpmakeFileType=1
		SET "sharpmakeFilename=Editor"
		CALL :createSharpmakeFile sharpmakeFilePath, sharpmakeFileType, sharpmakeFilename
		SET /A moduleAlreadyCreated=1
		SET modulePath=!modulesPath!
	)
)

IF !moduleAlreadyCreated!==0 (
	SET /P moduleName="Enter Module name: "

	IF NOT DEFINED moduleName (
		ECHO module name is not defined
		GOTO :end
	)

	SET modulePath=!modulesPath!!moduleName!
	ECHO try create !modulePath!
	IF NOT EXIST "!modulePath!" mkdir "!modulePath!"
	SET moduleFilePath=!modulePath!\Protostar.!moduleName!.Sharpmake.cs
	SET /A sharpmakeFileType=0
	ECHO try create !moduleFilePath!
	CALL :createSharpmakeFile moduleFilePath sharpmakeFileType moduleName
)

SET sourcePath=!modulePath!\Source
ECHO try create !sourcePath!
IF NOT EXIST "!sourcePath!" (
	mkdir "!sourcePath!"
	ECHO Sourcepath successfully created
) ELSE (
	ECHO Sourcepath already exists
)

SET privatePath=!sourcePath!\Private
SET publicPath=!sourcePath!\Public
ECHO try create !privatePath!
IF NOT EXIST "!privatePath!" (
	mkdir "!privatePath!"
	ECHO Private source path successfully created
) ELSE (
	ECHO Private source path already exists
)
ECHO try create !publicPath!
IF NOT EXIST "!publicPath!" ( 
	mkdir "!publicPath!"
	ECHO Public source path successfully created
) ELSE (
	ECHO Public source path already exists
)

SET /P loop="Do you want to create another module? (Y/N)"
IF !loop!==Y (
	GOTO :START
)

SET /P callBuildBatch="Do you want to run Build.bat? (Y/N)"

IF !callBuildBatch!==Y (
	CALL "Build.bat"
	EXIT /b %ERRORLEVEL%
)

PAUSE 
EXIT /b %ERRORLEVEL%

EXIT /b

:end
SET /P restart="Do you want to restart process? (Y/N) "
IF !restart!==Y (
	GOTO :START
)

PAUSE
EXIT /b %ERRORLEVEL%

REM *********  strlen function *****************************
:strlen <resultVar> <stringVar>
(   
    setlocal EnableDelayedExpansion
    (set^ tmp=!%~2!)
    if defined tmp (
        set "len=1"
        for %%P in (4096 2048 1024 512 256 128 64 32 16 8 4 2 1) do (
            if "!tmp:~%%P,1!" NEQ "" ( 
                set /a "len+=%%P"
                set "tmp=!tmp:~%%P!"
            )
        )
    ) ELSE (
        set len=0
    )
)
(
    endlocal
    set "%~1=%len%"
    exit /b
)

REM *********  createSharpmakeFile function *************************************************************
REM ********* param 2 = 0: Module template, 1: Executing project template	*****************************
:createSharpmakeFile <moduleFilePath> <moduleType> <moduleName>

SETLOCAL EnableDelayedExpansion

SET "sharpmakeTextFilePath="

CALL :CASE_!%~2!

IF EXIST !%~1! (
	SET /P overWrite="Do you want to overwrite the existing sharpmake file? (Y/N)"
		IF !overWrite!==Y (
			DEL /Q "!%~1!"
		) ELSE (
			GOTO :end
		)
	)

FOR /F %%N IN  ('FIND "" /v /c ^< "!sharpmakeTextFilePath!"') DO SET /A cnt=%%N

SET /A lines[!cnt!]

<!sharpmakeTextFilePath! (
	FOR /L %%N IN (1 1 %cnt%) DO (
		SET /P "str.%%N="
		
		SET lines[%%N]=!str.%%N!
		CALL :strlen len lines[%%N]
		IF NOT !len!==0 (
			CALL SET lines[%%N]=%%lines[%%N]:{ModuleName}=!%~3!%%
			ECHO !lines[%%N]!>>!%~1!
		) ELSE (
			ECHO.>>!%~1!
		)
	)
)

:end 
ENDLOCAL

EXIT /b

:CASE_0
	SET sharpmakeTextFilePath=%~dp0Snippets\CodeSnippets\SharpmakeModuleTemplate.cs
	GOTO CASE_END
:CASE_1 
	SET sharpmakeTextFilePath=%~dp0Snippets\CodeSnippets\SharpmakeExecutingTemplate.cs
	GOTO CASE_END
:CASE_END
	GOTO :eof
