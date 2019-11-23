---
marp: true
theme: gaia
backgroundColor: black
color: white
paginate: true
---

<style>
a {
    color: white
}
h1, h2, h3, h4, h5, h6 {
    color: #48b2e8
}
code, code[class*='language']{
    background: #222
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

- provide a simple way to obtain dependencies **in a reproducible manner**
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

---

### Buckaroo

- similar idea to [nix](https://nixos.org/nix/), but focused on build
- tightly integrated with [buck build system](https://buck.build)
- very difficult to integrate packages not using _buck build_
- _package_ is simply a link to repository commit

---

### Hunter

- tightly integrated with [CMake](https://cmake.org)
- supports sharing binary cache
    - not _binary packages_
- still difficult to work with (but very promising project)
    - e.g. not supporting latest toolchains, such as [Android NDK r20](https://docs.hunter.sh/en/latest/faq/android-studio.html#android-ndk-r19)
    - e.g. conflict resolution [must be done manually](https://docs.hunter.sh/en/latest/creating-new/create/cmake-dependencies.html#conflict)

---

### Vcpkg

- backed by Microsoft
- currently under active development
- not yet [supporting multiple versions of the same package](https://github.com/Microsoft/vcpkg/issues/4275)
- not yet [supporting specifying package versions in dependencies](https://github.com/Microsoft/vcpkg/issues/1681)

---

### Conan

- backed by JFrog
- supports reproducible builds
- supports both binary and source packages
    - friendly for distribution of proprietary libraries
- not tied to any specific build system
    - but has [integrations](https://docs.conan.io/en/latest/reference/generators.html) to most popular ones (CMake, Autotools, Visual Studio, Xcode, Scons, ...)
- written in Python (installable via `pip`)

---

### Conan (continued)

- all dependencies specified in `conanfile.txt`
- example:

```txt
[requires]
opencv/4.1.1@conan/stable
boost/1.71.0@conan/stable

[options]
boost:header_only=True

[imports]
res, haarcascades/haarcascade_frontalface_alt.xml -> .
```

---

### Conan - package installation

```txt
conan install /path/to/conanfile.txt [-g generator] [-s settings] [-o options]
```

or

```txt
conan install /path/to/conanfile.txt -pr profile
```

- generates an import file for specific build system using specified settings and options

---

# Conan demo

- project available at Github:
    - https://github.com/DoDoENT/cpp-meetups/tree/master/001_conan

---

### Dependency overriding

- possible to override dependencies' dependencies
    - some rebuilds may be necessary, but conan handles this automatically
    - by default, this depends on Semantic Versioning
        - but custom logic can be specified per package
- if conflicts occur, conan installation fails
    - user needs to resolve it

---

# TODO:
- creating packages
    - binary-only package support
- conan remotes
    - conan center, conan community, bincrafters
    - local instance (conan-server or Artifactory)
- advanced topics
    - recipe revisions
    - CI best practices

