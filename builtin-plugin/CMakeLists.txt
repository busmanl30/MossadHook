if (Plugin.ImportTableReplace AND SYSTEM.Darwin)
  message(STATUS "[Mossad] Enable got hook")
  include_directories(builtin-plugin/ImportTableReplace)
  add_subdirectory(builtin-plugin/ImportTableReplace)
endif ()

if (Plugin.Android.BionicLinkerUtil)
  if (NOT SYSTEM.Android)
    message(FATAL_ERROR "[!] Plugin.Android.BionicLinkerUtil only works on Android.")
  endif ()
  message(STATUS "[Mossad] Enable Plugin.Android.BionicLinkerUtil")
  set(mossad.plugin.SOURCE_FILE_LIST ${mossad.plugin.SOURCE_FILE_LIST}
    BionicLinkerUtil/bionic_linker_util.cc
    )
endif ()