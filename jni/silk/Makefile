# This makefile aim is only for now to address source checkout and patch
patches_files := $(wildcard patches/*.diff)

all :
	# For now we do nothing to build - it's made by android_toolchain
	
init : sources
	# Init done


sources :
	@wget http://developer.skype.com/silk/SILK_SDK_SRC_v1.0.8.zip; \
	unzip -q SILK_SDK_SRC_v1.0.8.zip; \
	mv SILK_SDK_SRC_v1.0.8 sources; \
	rm SILK_SDK_SRC_v1.0.8.zip

update :
	# For now no update for SILK
	
	
patch : .patched_sources
	@# Patch done

.patched_sources : $(patches_files)
	@quilt push -a && \
	touch .patched_sources

unpatch :
	@if [ -f .patched_sources ]; then quilt pop -af; rm .patched_sources; fi;