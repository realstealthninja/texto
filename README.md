<!--suppress ALL -->

<h1 align="center">Texto</h1>



<div align="center">
    Your one-stop shop for all things related to ascii.
</div>
<div align="center" markdown="1">

![texto-logo](assets/texto.svg)

</div>

<div align="center"> Texto is supposed to be an <a href=https://en.wikipedia.org/wiki/ASCII>ASCII</a> based renderer.</div>
<div align="center">

![License](https://img.shields.io/github/license/realstealthninja/texto?style=flat-square)
![Last commit](https://img.shields.io/github/last-commit/realstealthninja/texto?style=flat-square)
![Repository size](https://img.shields.io/github/repo-size/realstealthninja/texto?style=flat-square)
![build](https://img.shields.io/github/actions/workflow/status/realstealthninja/texto/build-project.yml?style=flat-square&logo=github)
[![Code Scanning](https://github.com/realstealthninja/texto/actions/workflows/codeql.yml/badge.svg)](https://github.com/realstealthninja/texto/actions/workflows/codeql.yml)

</div>

Table of contents
=================

<!--ts-->
* [Installation](#Installation)
* [Usage](#Usage)
* [Contributing](#Contribute)
<!--te-->

<a name="Installation"></a>
Installation
============

## Gitpod

By using Gitpod, you can skip all the steps which automatically installs all the necessary dependencies and builds the code.

[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/realstealthninja/texto)

## Locally

1. Clone the Git repository and its submodules.

```bash
git clone --recursive https://github.com/realstealthninja/texto.git
```

2. Install dependencies (Unix/Linux).

```bash
sudo apt-get update && sudo apt-get install ninja-build libopencv-dev
```

> **Note:**
>
> [Ninja Build](https://github.com/ninja-build/ninja/releases) and [OpenCV](https://github.com/opencv/opencv/releases) are also available for MacOs and Windows.

3. Build with CMake.

```bash
cmake -DCMAKE_BUILD_TYPE=Release -G Ninja -S ./ -B ./cmake-build-release
cmake --build ./cmake-build-release --target texto -j 1
```

Currently, Texto does not offer a prebuilt package. but it doesn't take a lot to compile.<br>
You can also run `build.sh`, which runs the exact same commands above.

<a name="Usage"></a>
Usage
=====

```bash
./texto <PATH-TO-FILE> <COLOURSPACE>
```

<a name="Contribute"></a>
Want to contribute?
===================

<p align="center">Great!</p>
First off all thank you for even considering contributing.
You can start by reading the <a href="./CODE_OF_CONDUCT.md">Code of Conduct</a> and contributing guidelines (TODO).

Please do raise an issue before opening a pull request discussing on how you are implementing the feature.
