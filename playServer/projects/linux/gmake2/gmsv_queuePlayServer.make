# Alternative GNU Make project makefile autogenerated by Premake

ifndef config
  config=releasewithsymbols_x86
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild

SHELLTYPE := posix
ifeq (.exe,$(findstring .exe,$(ComSpec)))
	SHELLTYPE := msdos
endif

# Configurations
# #############################################

RESCOMP = windres
INCLUDES += -I../../../source -isystem ../../../garrysmod_common/include -isystem ../../../garrysmod_common/helpers/include -isystem ../../../garrysmod_common/scanning/include -isystem ../../../garrysmod_common/detouring/include -isystem ../../../garrysmod_common/detouring/hde/include -isystem ../../../garrysmod_common/detouring/minhook/include -isystem ../../../garrysmod_common/sourcesdk-minimal/common -isystem ../../../garrysmod_common/sourcesdk-minimal/game/shared -isystem ../../../garrysmod_common/sourcesdk-minimal/public -isystem ../../../garrysmod_common/sourcesdk-minimal/game/server -isystem ../../../garrysmod_common/sourcesdk-minimal/public/tier0 -isystem ../../../garrysmod_common/sourcesdk-minimal/public/tier1
FORCE_INCLUDE +=
ALL_CPPFLAGS += $(CPPFLAGS) -MD -MP $(DEFINES) $(INCLUDES)
ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
define PREBUILDCMDS
endef
define PRELINKCMDS
endef
define POSTBUILDCMDS
endef

ifeq ($(config),releasewithsymbols_x86)
TARGETDIR = x86/ReleaseWithSymbols
TARGET = $(TARGETDIR)/gmsv_queuePlayServer_linux.dll
OBJDIR = x86/ReleaseWithSymbols/intermediate/gmsv_queuePlayServer
DEFINES += -DNDEBUG -DGMMODULE -DQUEUEPLAYSERVER_SERVER -DIS_SERVERSIDE=true -DGMOD_ALLOW_OLD_TYPES -DGMOD_ALLOW_LIGHTUSERDATA -DGMOD_MODULE_NAME=\"queuePlayServer\" -DGAME_DLL -DRAD_TELEMETRY_DISABLED -DGMOD_USE_SOURCESDK -DCOMPILER_GCC -DPOSIX -D_POSIX -DLINUX -D_LINUX -DGNUC -DNO_MALLOC_OVERRIDE
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m32 -Wshadow -Wundef -Og -fPIC -fstrict-aliasing -Wstrict-aliasing=3 -g -msse2 -Wall -Wextra -std=gnu11 -Wno-unused-local-typedefs -Wno-unused-parameter -Wno-strict-aliasing -Wno-unknown-pragmas -Wno-undef -Wno-invalid-offsetof
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m32 -Wshadow -Wundef -Og -fPIC -fstrict-aliasing -Wstrict-aliasing=3 -g -msse2 -Wall -Wextra -std=gnu++17 -Wno-unused-local-typedefs -Wno-unused-parameter -Wno-strict-aliasing -Wno-unknown-pragmas -Wno-undef -Wno-invalid-offsetof
LIBS += ../../../garrysmod_common/projects/linux/gmake2/x86/ReleaseWithSymbols/libhelpers.a ../../../garrysmod_common/projects/linux/gmake2/x86/ReleaseWithSymbols/liblua_shared.a ../../../garrysmod_common/scanning/projects/linux/gmake2/x86/ReleaseWithSymbols/libscanning.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/ReleaseWithSymbols/libdetouring.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/ReleaseWithSymbols/libminhook.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/ReleaseWithSymbols/libhde.a ../../../garrysmod_common/sourcesdk-minimal/projects/linux/gmake2/x86/ReleaseWithSymbols/libtier1.a ../../../garrysmod_common/sourcesdk-minimal/projects/linux/gmake2/x86/ReleaseWithSymbols/libLZMA.a -ldl -ltier0_srv -lvstdlib_srv
LDDEPS += ../../../garrysmod_common/projects/linux/gmake2/x86/ReleaseWithSymbols/libhelpers.a ../../../garrysmod_common/projects/linux/gmake2/x86/ReleaseWithSymbols/liblua_shared.a ../../../garrysmod_common/scanning/projects/linux/gmake2/x86/ReleaseWithSymbols/libscanning.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/ReleaseWithSymbols/libdetouring.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/ReleaseWithSymbols/libminhook.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/ReleaseWithSymbols/libhde.a ../../../garrysmod_common/sourcesdk-minimal/projects/linux/gmake2/x86/ReleaseWithSymbols/libtier1.a ../../../garrysmod_common/sourcesdk-minimal/projects/linux/gmake2/x86/ReleaseWithSymbols/libLZMA.a
ALL_LDFLAGS += $(LDFLAGS) -L../../../garrysmod_common/sourcesdk-minimal/lib/public/linux32 -L/usr/lib32 -m32 -shared -Wl,-soname=gmsv_queuePlayServer_linux.dll -Wl,--no-undefined

else ifeq ($(config),release_x86)
TARGETDIR = x86/Release
TARGET = $(TARGETDIR)/gmsv_queuePlayServer_linux.dll
OBJDIR = x86/Release/intermediate/gmsv_queuePlayServer
DEFINES += -DNDEBUG -DGMMODULE -DQUEUEPLAYSERVER_SERVER -DIS_SERVERSIDE=true -DGMOD_ALLOW_OLD_TYPES -DGMOD_ALLOW_LIGHTUSERDATA -DGMOD_MODULE_NAME=\"queuePlayServer\" -DGAME_DLL -DRAD_TELEMETRY_DISABLED -DGMOD_USE_SOURCESDK -DCOMPILER_GCC -DPOSIX -D_POSIX -DLINUX -D_LINUX -DGNUC -DNO_MALLOC_OVERRIDE
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m32 -Wshadow -Wundef -flto -O3 -fPIC -fstrict-aliasing -Wstrict-aliasing=3 -msse2 -Wall -Wextra -std=gnu11 -Wno-unused-local-typedefs -Wno-unused-parameter -Wno-strict-aliasing -Wno-unknown-pragmas -Wno-undef -Wno-invalid-offsetof
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m32 -Wshadow -Wundef -flto -O3 -fPIC -fstrict-aliasing -Wstrict-aliasing=3 -msse2 -Wall -Wextra -std=gnu++17 -Wno-unused-local-typedefs -Wno-unused-parameter -Wno-strict-aliasing -Wno-unknown-pragmas -Wno-undef -Wno-invalid-offsetof
LIBS += ../../../garrysmod_common/projects/linux/gmake2/x86/Release/libhelpers.a ../../../garrysmod_common/projects/linux/gmake2/x86/Release/liblua_shared.a ../../../garrysmod_common/scanning/projects/linux/gmake2/x86/Release/libscanning.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/Release/libdetouring.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/Release/libminhook.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/Release/libhde.a ../../../garrysmod_common/sourcesdk-minimal/projects/linux/gmake2/x86/Release/libtier1.a ../../../garrysmod_common/sourcesdk-minimal/projects/linux/gmake2/x86/Release/libLZMA.a -ldl -ltier0_srv -lvstdlib_srv
LDDEPS += ../../../garrysmod_common/projects/linux/gmake2/x86/Release/libhelpers.a ../../../garrysmod_common/projects/linux/gmake2/x86/Release/liblua_shared.a ../../../garrysmod_common/scanning/projects/linux/gmake2/x86/Release/libscanning.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/Release/libdetouring.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/Release/libminhook.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/Release/libhde.a ../../../garrysmod_common/sourcesdk-minimal/projects/linux/gmake2/x86/Release/libtier1.a ../../../garrysmod_common/sourcesdk-minimal/projects/linux/gmake2/x86/Release/libLZMA.a
ALL_LDFLAGS += $(LDFLAGS) -L../../../garrysmod_common/sourcesdk-minimal/lib/public/linux32 -L/usr/lib32 -m32 -flto -shared -Wl,-soname=gmsv_queuePlayServer_linux.dll -s -Wl,--no-undefined

else ifeq ($(config),debug_x86)
TARGETDIR = x86/Debug
TARGET = $(TARGETDIR)/gmsv_queuePlayServer_linux.dll
OBJDIR = x86/Debug/intermediate/gmsv_queuePlayServer
DEFINES += -DDEBUG -D_DEBUG -DGMMODULE -DQUEUEPLAYSERVER_SERVER -DIS_SERVERSIDE=true -DGMOD_ALLOW_OLD_TYPES -DGMOD_ALLOW_LIGHTUSERDATA -DGMOD_MODULE_NAME=\"queuePlayServer\" -DGAME_DLL -DRAD_TELEMETRY_DISABLED -DGMOD_USE_SOURCESDK -DCOMPILER_GCC -DPOSIX -D_POSIX -DLINUX -D_LINUX -DGNUC -DNO_MALLOC_OVERRIDE
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m32 -Wshadow -Wundef -O0 -fPIC -fstrict-aliasing -Wstrict-aliasing=3 -g -msse2 -Wall -Wextra -std=gnu11 -Wno-unused-local-typedefs -Wno-unused-parameter -Wno-strict-aliasing -Wno-unknown-pragmas -Wno-undef -Wno-invalid-offsetof
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m32 -Wshadow -Wundef -O0 -fPIC -fstrict-aliasing -Wstrict-aliasing=3 -g -msse2 -Wall -Wextra -std=gnu++17 -Wno-unused-local-typedefs -Wno-unused-parameter -Wno-strict-aliasing -Wno-unknown-pragmas -Wno-undef -Wno-invalid-offsetof
LIBS += ../../../garrysmod_common/projects/linux/gmake2/x86/Debug/libhelpers.a ../../../garrysmod_common/projects/linux/gmake2/x86/Debug/liblua_shared.a ../../../garrysmod_common/scanning/projects/linux/gmake2/x86/Debug/libscanning.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/Debug/libdetouring.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/Debug/libminhook.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/Debug/libhde.a ../../../garrysmod_common/sourcesdk-minimal/projects/linux/gmake2/x86/Debug/libtier1.a ../../../garrysmod_common/sourcesdk-minimal/projects/linux/gmake2/x86/Debug/libLZMA.a -ldl -ltier0_srv -lvstdlib_srv
LDDEPS += ../../../garrysmod_common/projects/linux/gmake2/x86/Debug/libhelpers.a ../../../garrysmod_common/projects/linux/gmake2/x86/Debug/liblua_shared.a ../../../garrysmod_common/scanning/projects/linux/gmake2/x86/Debug/libscanning.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/Debug/libdetouring.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/Debug/libminhook.a ../../../garrysmod_common/detouring/projects/linux/gmake2/x86/Debug/libhde.a ../../../garrysmod_common/sourcesdk-minimal/projects/linux/gmake2/x86/Debug/libtier1.a ../../../garrysmod_common/sourcesdk-minimal/projects/linux/gmake2/x86/Debug/libLZMA.a
ALL_LDFLAGS += $(LDFLAGS) -L../../../garrysmod_common/sourcesdk-minimal/lib/public/linux32 -L/usr/lib32 -m32 -shared -Wl,-soname=gmsv_queuePlayServer_linux.dll -Wl,--no-undefined

endif

# Per File Configurations
# #############################################


# File sets
# #############################################

GENERATED :=
OBJECTS :=

GENERATED += $(OBJDIR)/module.o
OBJECTS += $(OBJDIR)/module.o

# Rules
# #############################################

all: $(TARGET)
	@:

$(TARGET): $(GENERATED) $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking gmsv_queuePlayServer
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning gmsv_queuePlayServer
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(GENERATED)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(GENERATED)) del /s /q $(subst /,\\,$(GENERATED))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild: | $(OBJDIR)
	$(PREBUILDCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) | $(PCH_PLACEHOLDER)
$(GCH): $(PCH) | prebuild
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
$(PCH_PLACEHOLDER): $(GCH) | $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) touch "$@"
else
	$(SILENT) echo $null >> "$@"
endif
else
$(OBJECTS): | prebuild
endif


# File Rules
# #############################################

$(OBJDIR)/module.o: ../../../source/module.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(PCH_PLACEHOLDER).d
endif