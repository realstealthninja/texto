![License](https://img.shields.io/github/license/realstealthninja/texto?style=flat-square)
![Last commit](https://img.shields.io/github/last-commit/realstealthninja/texto?style=flat-square)
![Repository size](https://img.shields.io/github/repo-size/realstealthninja/texto?style=flat-square)

<!--suppress ALL -->

<h1 align="center">Texto</h1>

<p align="center">
Your one-stop shop for all things related to ascii.
</p>

<p align="center">
<img src="./examples/texto.svg" height="300" width="300" alt="texto-logo">
</p>



<p align="center"> Texto is supposed to be an <a href=https://en.wikipedia.org/wiki/ASCII>ASCII</a> based renderer.</p>

Table of contents
=================

<!--ts-->
* [Installation](#Installation)
* [Usage](#Usage)
* [Contributing](#Want-to-contribute?)
<!--te-->

Installation
============

Right now Texto does not offer a prebuilt package. but it does not take a lot to compile

```bash
cmake -DCMAKE_BUILD_TYPE=Release -G Ninja -S ./ -B ./cmake-build-release
cmake --build ./cmake-build-release --target texto -j 1
```

or run build.sh

Usage
=====

```bash
./texto <PATH-TO-FILE> <COLOURSPACE>
```

Want to contribute?
===================

<p align="center">Great!</p>
First off all thank you for even considering contributing.
You can start by reading the <a href="./CODE_OF_CONDUCT.md">Code of Conduct</a> and contributing guidelines (TODO).

Please do raise an issue before opening a pull request discussing on how you are implementing the feature.
