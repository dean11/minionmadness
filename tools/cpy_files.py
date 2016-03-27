import glob
import sys
import shutil



def main():
	if(len(sys.argv) < 2):
		print("No files copied from cpy_files.py")
		return
	src = sys.argv[1]
	dest = sys.argv[2]
	
	for file in glob.glob(src):
		print ("Copying " + file)
		shutil.copy2(file, dest)
	
	
	
if __name__ == "__main__":
    main()