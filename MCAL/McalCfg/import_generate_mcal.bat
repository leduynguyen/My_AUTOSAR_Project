@echo on
set ARCTICSTUDIO=%1
set ECUC_PROJECT=%~dp0
set CORE=%~dp0../core
set WORKSPACE=C:\temp\workspace
set PROJECT=MCAL_Cfg
set ECUC=stm32f107/Collections
set OUTPUT=./McalGen

set IMPL_Can=Can,/ArcCore/Implementations/stm32f107/Can
set IMPL_Dio=Dio,/ArcCore/Implementations/stm32f107/Dio
set IMPL_Gpt=Gpt,/ArcCore/Implementations/stm32f107/Gpt
set IMPL_Mcu=Mcu,/ArcCore/Implementations/stm32f107/Mcu
set IMPL_Port=Port,/ArcCore/Implementations/stm32f107/Port

set IMPLEMENTATION=%IMPL_Can%;%IMPL_Dio%;%IMPL_Gpt%;%IMPL_Mcu%;%IMPL_Port%
@echo on

rmdir /s /q %WORKSPACE%
call %ARCTICSTUDIO% -application com.arccore.cli.projectimporter -project %CORE% -data %WORKSPACE%
call %ARCTICSTUDIO% -application com.arccore.cli.projectimporter -project %ECUC_PROJECT% -data %WORKSPACE%

call %ARCTICSTUDIO% -application com.arccore.cli.generator -project %PROJECT% -ecuc %ECUC% -data %WORKSPACE% -output %OUTPUT% -implementations %IMPLEMENTATION% -nosplash -verbosity DEBUG

