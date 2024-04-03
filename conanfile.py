from conan import ConanFile

class Interpreter(ConanFile):
	generators = ("CMakeToolchain", "CMakeDeps")
	settings = ("os", "build_type", "arch", "compiler")

	def requirements(self):
		self.requires("gtest/1.14.0")

	def build_requirements(self):
		self.tool_requires("cmake/[>=3.25]")

	def layout(self):
		self.folders.generators = ""