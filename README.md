# passm  
____________________  
A command-line interface for password managing  
  
## setup  
To start it, run **passm init**  
To set personal defaults, run **passm setpd** (explained in usage)  
## usage  
**passm \<command\> \<args...\> [options...]**  
Any unset arguements for a command will be prompted for  
Right now, all arguements must be in the order specified  
Commands:  
* **add \<name\> [-d/-pd/\<size\>]**: add password of <name>   with either defaults or specified size   
    - A password will have at least a symbol, number, and letter  
    - -d: normal defaults  
    - -pd: personal defaults set through **setpd**  
    - If not using defaults but using \<size\>, it will prompt you for symbols  
    - If no options given, it will prompt you for both size and symbols  
* **get \<name\>**: get password of \<name\> if it exists
    - \<name\>: name of password  
* **set \<name\> \<password\>**: set password of \<name\> to \<password\>  
    - \<name\>: name of password  
    - \<password\>: new password   
* **passm setpd \<size\>**: set personal defaults of size and symbols  
    - Will prompt you for symbols  
    - Current default symbols: ><!@#$%^&*/?_+-=  