# OS Project - Development Guide

## 🛠 Prerequisites

### All Team
- **Git** ([Windows](https://git-scm.com/download/win) | [Linux](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git))
- **GitSetup** ([ How to Install and Configure Git and GitHub on Windows 11 ](https://youtu.be/AdzKzlp66sQ?si=JyVO4AeBYRZiIFOV))
- **C++ Toolchain**:
    - *Windows*: MinGW-w64 or Visual Studio Build Tools
    - *Linux*: `sudo apt install build-essential g++ make cmake`

### Optional (Recommended)
- **CLion** or **VS Code** (with C++ extensions)

---

##  Step 1: Clone the Repository
```sh
git clone https://github.com/Ahmed-Hekal-01/OS_Project.git
cd OS_Project
```
#  Essential Git Commands

##  Sync with Remote
### Download latest changes
```sh
git pull origin main
```
### stage all changes
```sh
git add .
```
### Commit with message
```sh
git commit -m "Describe your changes"
```
### Upload your changes
```sh
git push origin main
```