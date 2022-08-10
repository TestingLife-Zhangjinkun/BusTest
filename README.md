# BusTest
A lightweight bus testing framework developed based on Qt subdirectory project and C++ shared library.

Hi everyone, I am @TestingLife - Zhangjinkun and I have been working on software testing for more than **15 years**. My interests are mainly in the technical research related to **software testing** and **test tool development**. I have some scientific achievements in the field of software automation testing, especially in bus communication interface based software automation testing, and automatic test data generation, see [my ORCID](https://orcid.org/0000-0003-4506-3235) for details.

This project is a lightweight data simulation test framework proposed for bus communication-based software. It supports the flexible construction of a semi-physical simulation test environment and can implement automated testing without developing test scripts. The purpose of building this project is, on the one hand, to share the author's experience in equipment software testing, on the other hand, to work with collaborators from all over the world for the progress of the software testing industry.

This project is planned to be implemented in three phases.
In the first phase, design a lightweight bus testing framework, define a unified plug-in interface, and implement a GUI application that inherits from QMainWindow. Designing the plug-in configuration interface makes it possible for users to configure the plug-in type and the number of plug-in forms as needed, thus initializing the framework with minimal resources and simplifying operations.

In the second stage, design single bus interface test plug-ins based on Qt Plugins to form a plug-in set to simulate the peripheral data of SUT. The idea of keyword-driven testing is introduced to design unified data configuration rules, making it possible for testers to make simple configurations to implement automated testing, thus reducing the technical threshold of automated testing. The authors plan to implement the following single bus interfaces: serial, UDP, TCP, CAN, 1553B, and hope that other collaborators will enrich other bus interface test plug-ins.

In the third phase, the data configuration rules are extended, and the test framework and test plugins are upgraded at the same time. I hope that the upgrade will enable data exchange between different types of bus interfaces and further extend the application scope of this project.


Thanks! :sparkling_heart:
