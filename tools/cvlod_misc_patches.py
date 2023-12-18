import sys

ROM = sys.argv[1]
hook_overlay = sys.argv[2]

def writeBytesToROM(value, address, ROM_file):
	ROM_file.seek(address)
	ROM_file.write(value)

# Entrypoint address for the overlay's code (0x0F000000 since the overlay is gonna be mapped there by the TLB)
def patch_patchEntrypointAddress(ROM_file):
	writeBytesToROM(0x0F000000.to_bytes(4, 'big'), 0xAE258, ROM_file)

# Change module ID from 0x0006 -> 0x2006
def patch_patchModuleID(ROM_file):
	writeBytesToROM(0x07002006.to_bytes(4, 'big'), 0xADC8C, ROM_file)

# Create the "file info" struct associated to the overlay at RAM address 0x800BCC20
# (only replaces file 2, which is the unused debug font assets file in the vanilla ROM)
def patch_createFileInfo(ROM_file):
	writeBytesToROM(0x800BCC20.to_bytes(4, 'big'), 0xAF6A4, ROM_file)
	writeBytesToROM(0x40000002.to_bytes(4, 'big'), 0xBD820, ROM_file)
	writeBytesToROM(0x00001000.to_bytes(4, 'big'), 0xBD824, ROM_file)

# Patch gameplayMgr's code so that it doesn't spawn module 0x0006
# (which we're repurposing for this mod)
def patch_instancesWhenModule0006IsSpawned(ROM_file):
	writeBytesToROM(0x00000000.to_bytes(4, 'big'), 0x1B518, ROM_file)
	writeBytesToROM(0x00000000.to_bytes(4, 'big'), 0x1B558, ROM_file)

# The Test Grid map only has one actor, module 0006...
# Also makes the Test Grid map work without Gameshark codes
def patch_removeActorsFromTestGrid(ROM_file):
	writeBytesToROM(0x00000000.to_bytes(4, 'big'), 0x10D460, ROM_file)
	writeBytesToROM(0x00000000.to_bytes(4, 'big'), 0x10D464, ROM_file)
	writeBytesToROM(0x00000000.to_bytes(4, 'big'), 0x10D468, ROM_file)

# Add a reference in the gameplay gamestate data
# so that the game can branch to the stage select open button check code
def patch_patchAddHook(ROM_file):
	writeBytesToROM(0xA00BCC28.to_bytes(4, 'big'), 0xADD08, ROM_file)

# Load the stage select open button check code (hook.ovl) at RAM address 0x800BCC28
def patch_patchAddHookCode(hook_overlay, ROM_file):
	writeBytesToROM(hook_overlay.read(), 0xBD828, ROM_file)

if __name__ == "__main__":
	with open(ROM, "r+b") as ROM_file:
		patch_patchEntrypointAddress(ROM_file)
		patch_patchModuleID(ROM_file)
		patch_createFileInfo(ROM_file)
		patch_instancesWhenModule0006IsSpawned(ROM_file)
		patch_removeActorsFromTestGrid(ROM_file)

		with open(hook_overlay, "r+b") as hook_overlay:
			patch_patchAddHook(ROM_file)
			patch_patchAddHookCode(hook_overlay, ROM_file)