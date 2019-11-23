from conans import ConanFile, CMake, tools


class FacecameraConan(ConanFile):
    name = "face-camera"
    version = "0.1.0"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake"
    scm = {
        "type": "git",
        "url": "auto",
        "revision": "auto"
    }
    requires = (
        'opencv/4.1.1@conan/stable',
        'boost/1.71.0@conan/stable'
    )
    no_copy_source = True

    def configure(self):
        self.options['boost'].header_only = True

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder='sample-lib')
        cmake.build()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["face_camera"]

