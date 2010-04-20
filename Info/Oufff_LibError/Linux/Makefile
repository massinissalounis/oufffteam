# Headers
DLL_NAME = Oufff_LibError
DLL_VERSION = 1.0.3

SRC_DIR = ../src/
INCLUDE_DIR = ../include
ADDITIONNAL_LIB = ""

DISABLE_WARNING = -Wno-deprecated
DEBUG = -g -Wall
# -------



all: clean precompil $(DLL_NAME) postcompil
export: clean precompil $(DLL_NAME) preexport export_lib postcompil

# Display --------------------------------------------

clean:
	rm -f -r *.o *.so *~ && clear

precompil:
	@echo "------------------------- Creation of $(DLL_NAME).so.$(DLL_VERSION) -------------------------"
	@echo " "
	@echo " # Compiling code : "

preexport:
	@echo " "
	@echo " # Exporting files into OufffLib (New version used = $(DLL_VERSION)) : "

postcompil:
	@echo " "
	@echo "--------------------- End of compilation $(DLL_NAME).so.$(DLL_VERSION) ----------------------"
	@echo " "


# Compilation Rules ----------------------------------

Oufff_LibError: 
	$(CXX) $(SRC_DIR)Oufff_LibError.cpp -c -o $@.so.$(DLL_VERSION) -I$(INCLUDE_DIR) -shared 



# Export Rules ---------------------------------------

export_lib:	export_dll export_inc make_link


export_dll:
	cp $(DLL_NAME).so.$(DLL_VERSION) ../../OufffLib/Linux/$(DLL_NAME).so.$(DLL_VERSION)
	
	
export_inc:
	cp $(INCLUDE_DIR)/$(DLL_NAME).h ../../OufffLib/Include/Linux/$(DLL_NAME)-$(DLL_VERSION).h

make_link:
	cd ../../OufffLib/Include/Linux/ && rm -f $(DLL_NAME).h && ln -s $(DLL_NAME)-$(DLL_VERSION).h $(DLL_NAME).h && cd -
	cd ../../OufffLib/Linux/ && rm -f $(DLL_NAME).so && ln -s $(DLL_NAME).so.$(DLL_VERSION) $(DLL_NAME).so && cd -
