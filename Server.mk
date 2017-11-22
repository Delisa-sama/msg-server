##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Server
ConfigurationName      :=Debug
WorkspacePath          :=/home/delisa/Documents/test
ProjectPath            :=/home/delisa/Documents/test/messanger-server-part
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=delisa
Date                   :=18/11/17
CodeLitePath           :=/home/delisa/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Server.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lboost_thread -lboost_system
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/home/delisa/Downloads/boostlib/include/ 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/home/delisa/Downloads/boostlib/lib/ 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -std=c++11 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
LD_LIBRARY_PATH:=/home/delisa/Downloads/boostlib/lib/
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/server.cpp$(ObjectSuffix) $(IntermediateDirectory)/listener.cpp$(ObjectSuffix) $(IntermediateDirectory)/receiver.cpp$(ObjectSuffix) $(IntermediateDirectory)/getBlock.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/delisa/Documents/test/messanger-server-part/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/server.cpp$(ObjectSuffix): server.cpp $(IntermediateDirectory)/server.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/delisa/Documents/test/messanger-server-part/server.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/server.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/server.cpp$(DependSuffix): server.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/server.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/server.cpp$(DependSuffix) -MM server.cpp

$(IntermediateDirectory)/server.cpp$(PreprocessSuffix): server.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/server.cpp$(PreprocessSuffix) server.cpp

$(IntermediateDirectory)/listener.cpp$(ObjectSuffix): listener.cpp $(IntermediateDirectory)/listener.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/delisa/Documents/test/messanger-server-part/listener.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/listener.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/listener.cpp$(DependSuffix): listener.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/listener.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/listener.cpp$(DependSuffix) -MM listener.cpp

$(IntermediateDirectory)/listener.cpp$(PreprocessSuffix): listener.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/listener.cpp$(PreprocessSuffix) listener.cpp

$(IntermediateDirectory)/receiver.cpp$(ObjectSuffix): receiver.cpp $(IntermediateDirectory)/receiver.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/delisa/Documents/test/messanger-server-part/receiver.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/receiver.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/receiver.cpp$(DependSuffix): receiver.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/receiver.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/receiver.cpp$(DependSuffix) -MM receiver.cpp

$(IntermediateDirectory)/receiver.cpp$(PreprocessSuffix): receiver.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/receiver.cpp$(PreprocessSuffix) receiver.cpp

$(IntermediateDirectory)/getBlock.cpp$(ObjectSuffix): getBlock.cpp $(IntermediateDirectory)/getBlock.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/delisa/Documents/test/messanger-server-part/getBlock.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/getBlock.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/getBlock.cpp$(DependSuffix): getBlock.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/getBlock.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/getBlock.cpp$(DependSuffix) -MM getBlock.cpp

$(IntermediateDirectory)/getBlock.cpp$(PreprocessSuffix): getBlock.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/getBlock.cpp$(PreprocessSuffix) getBlock.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


