SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Program Files\Microsoft MPI\Bin\;C:\Program Files (x86)\IntelSWToolsMPI\compilers_and_libraries_2018.5.274\windows\mpi\intel64\bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files (x86)\wapt;C:\Program Files (x86)\IVI Foundation\IVI\bin;C:\Program Files\IVI Foundation\IVI\bin;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin\;C:\Program Files\IVI Foundation\VISA\Win64\Bin\;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin;C:\Program Files\Git\cmd;C:\Program Files\Microsoft VS Code\bin;c:\Program Files\PuTTY\;C:\Users\rrenoux\AppData\Local\Microsoft\WindowsApps;
SET CPU_TYPE=LPC1768
SET CPU_VENDOR=NXP
SET UV2_TARGET=Open1786
SET CPU_CLOCK=0x00B71B00
"C:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\output\startup_lpc17xx._ia"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\system_lpc17xx.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\core_cm3.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_clkpwr.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_gpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_pinsel.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_timer.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_exti.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_nvic.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_ssp.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_i2c.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\ili_lcd_general.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lcd_api.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\english_16x8.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\affichagelcd.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\touch_panel.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\memoire.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\timer1.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\pin.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\morpion.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\Output\Project.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\Output\Project.axf" --i32combined --output ".\Output\Project.hex"
