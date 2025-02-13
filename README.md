# SystemC
SystemC Learning <br>
## Table of Content
- [Introduction](#introduction)
- [Installation](#installation)
- [SystemC Basics](#systemC_basics)
- [SystemC Consepts](#systemC_consepts)
- [How to Simulate SystemC Code](#how_to_simulate_systemc_code)
# Introduction
SystemC is a set of C++ classes and macros that provide an event-driven simulation kernel, making it a powerful tool for system-level modeling and verification of hardware designs. It extends C++ to enable modeling of concurrent processes, hardware timing, and synchronization, making it widely used in hardware design and verification.
This repository serves as a learning resource for SystemC, providing fundamental concepts, example code, and best practices to help engineers understand how to model and simulate hardware components efficiently.<br>
# Installation
To use SystemC, follow these steps:<br>
**Prerequisites**
- A C++ compiler (GCC, Clang, or MSVC)
- CMake (optional but recommended for building projects)
- SystemC library
**Installation steps for Windows**
- Download the SystemC package from Accellera.
- Extract and set up the environment variables (SYSTEMC_HOME and INCLUDE, LIB paths).
- Compile using MSVC or MinGW
# SystemC Basics
SystemC provides various constructs for hardware modeling, such as modules, processes, signals, and event-driven execution.
**1. Basic SystemC Structure**
A basic SystemC module consists of:
- sc_module: Represents a hardware component.
- sc_signal: Used for communication between modules.
- sc_process: Describes concurrent behavior using SC_THREAD or SC_METHOD.<br>
# SystemC Concepts
**1. Modules and Hierarchy**<br>
SystemC designs are composed of sc_module objects, allowing hierarchical modeling.<br>
**2. Data Types**<br>
SystemC defines its own data types for hardware modeling:
- sc_uint<N>: Unsigned integer of N bits
- sc_int<N>: Signed integer of N bits
- sc_logic and sc_lv<N>: Logic values and logic vectors<br>

**3. Processes**<br>
Processes define the behavior of modules. There are three types:
- SC_METHOD: Executes once per event trigger (no internal wait).
- SC_THREAD: Runs as a thread with wait() statements.
- SC_CTHREAD: Used for clocked processes.<br>

**4. Signals and Ports**
- sc_signal<T>: Connects modules by transferring values between them.
- sc_in<T> and sc_out<T>: Input and output ports for communication.<br>

**5. Simulation and Timing**
SystemC includes sc_time for defining time delays and event scheduling.<br>
# How to Simulate SystemC Code?
To configure SystemC for simulation in Visual Studio, follow these steps:<br>
Open systemC.sln in Visual Studio and click Build.<br>
Create a New Project via File → New Project.<br>
**Set Up Project Properties:** <br>
=> VC++ Settings:<br>
**Include Directories** → Set to path navigating to src folder.<br>
**Library Directories** → Set to path navigating to debug folder.<br>
=> C++ Settings:<br>
**Language** → ISO C++17 Standard (/std:c++17) or higher.<br>
**Command Line** → Add /vmg.<br>
=> Linker Settings:<br>
**Input** → Additional Dependencies → Add SystemC.lib.<br>
**General** → Additional Library Directory → Set to debug folder.<br>
Click **Apply** and **OK**.<br>
Include all necessary source files.<br>
Press Ctrl+Shift+B to build the project.<br>
Open Local Windows Debugger to view the simulated results.<br>



