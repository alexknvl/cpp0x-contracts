newaction {
  trigger = 'clean',
  description = 'Cleans up the project.',
  shortname = "clean",
  
  execute = function()
    os.rmdir("bin")
    os.rmdir("build")
  end
}

solution "c++0x-contracts"
  configurations { "debug", "release" }
  platforms { "x32", "x64" }

  location "build"
  
  for _,arch in pairs({"x32", "x64"}) do
    for _,conf in pairs({"debug", "release"}) do
      for _,plat in pairs({"vs2008"}) do
        configuration { arch, conf, plat }
          targetdir(path.join("bin", path.join(plat, path.join(arch, conf))))
      end
    end
  end
  
  flags { "FatalWarnings", "ExtraWarnings" }
  
  configuration { "windows" }
    defines { "WIN32", "_WIN32" }
    defines { "_CRT_SECURE_NO_WARNINGS", "_CRT_NONSTDC_NO_DEPRECATE" }
    
  configuration { "debug" }
    defines { "DEBUG" }
    flags { "Symbols" }

  configuration { "release" }
    defines { "NDEBUG" }
    flags { "Optimize" }
  
  project "SampleApp"
    kind "ConsoleApp"
    language "C++"
    
    links "CppContracts"
    
    includedirs { "src" }
    files { "src/SampleApp/**.cpp",
            "src/SampleApp/**.hpp" }
  
  project "CppContracts"
    kind "StaticLib"
    language "C++"
    
    includedirs { "src" }
    files { "src/CppContracts/**.cpp",
            "src/CppContracts/**.hpp" }