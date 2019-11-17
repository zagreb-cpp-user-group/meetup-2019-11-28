---
marp: true
theme: gaia
backgroundColor: #538DC1
color: white
---

<style>
a {
    color: white
}
</style>

<!-- _class: lead -->

# C/C++ development with package managers

---

# Package manager

- from [Wikipedia](https://en.wikipedia.org/wiki/Package_manager):
    - _a collection of software tools that automates the process of installing, upgrading, configuring, and removing computer programs for a computer's operating system in a consistent manner_

- types:
    - system package managers (e.g. `apt-get`, `yum`, `brew`, `chocolate`)
    - application package managers (e.g. VSCode Extension Manager)
    - development package managers

---

## Development package managers

- provide a simple way to obtain dependencies **in a reproducable manner**
    - support handling multiple versions of the same package
- provide a facility to update dependencies
- support resolving conflicts between dependencies
- **integrate well with the build system**
- reduce build times

---

## Other languages

- Python: `pip`, `easy_install`
- JavaScript: `npm`
- Java: `maven`, `gradle`
- Ruby: `gem`
- Rust: `cargo`
- C#: `nuget`

---

## C/C++

- main problem:
    - _build system integration_
    - no standard build system for C/C++

---

## C/C++ - current solutions

- [Conan](https://conan.io)
- [vcpkg](https://github.com/microsoft/vcpkg)
- [hunter](https://docs.hunter.sh/en/latest/)
- [buckaroo](https://buckaroo.pm)
