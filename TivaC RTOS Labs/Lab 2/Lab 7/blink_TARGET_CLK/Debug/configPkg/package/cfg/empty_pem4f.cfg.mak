# invoke SourceDir generated makefile for empty.pem4f
empty.pem4f: .libraries,empty.pem4f
.libraries,empty.pem4f: package/cfg/empty_pem4f.xdl
	$(MAKE) -f C:\Users\itzel\workspace_v9\blink_TARGET_CLK/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\itzel\workspace_v9\blink_TARGET_CLK/src/makefile.libs clean

