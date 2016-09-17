import sys
import shutil
import os
from os import listdir
from os.path import isfile, join
import getopt

def main():
	try:
		opts, args = getopt.getopt(sys.argv[1:], "p:f:d:D:r:R:x:", ["x64", "x86", "debug", "Debug", "release", "Release", "dry-run"])
		
	except getopt.GetoptError as err:
		print(err)
		return
	
	arc = "x86"
	mode = "Debug"
	project = "MinionGraphics"
	files = []
	
	for	opt, arg in opts:
		opt = opt.lower()
		if opt == "-d" or opt == "-D" or opt == "debug":
			mode = "Debug"
		elif opt == "-r" or opt == "-R" or opt == "release":
			mode = "Release"
		elif opt == "--x86":
			arc = "x86"
		elif opt == "--x64":
			arc = "x64"
		elif opt == "-x":
			if arg == "86" or arg == "64":
				arc = "x" + arg
				pitraceDir = "D:/apitrace/x" + arg + "/bin/"
		elif opt =="-f":
			files = arg.split(" ")
		elif opt == "-p":
			project = arg;
		elif opt == "--dry-run":
			return
			
	cwd = os.path.dirname(os.path.realpath(__file__)) + "/"
	src = cwd + "../external/bin/" + arc + "/"
	destDir = cwd + "/../output/" + project + "/" + arc + "/" + mode + "/"
	
	if not os.path.exists(destDir):
		os.makedirs(destDir)
	
	print ("Destination directory: \"" + destDir + "\"")
	
	if len(files) == 0:
		onlyfiles = [f for f in listdir(src) if isfile(join(src, f))]
		
		for file in onlyfiles:
			f = join(src, file)
			print ("Copying " + file)
			#dst = os.path.join(destDir, os.path.basename(file))
			shutil.copy(f, destDir)
	else:
		for file in files:
			print ("Copying " + file)
			shutil.copy(file, destDir)
	
if __name__ == "__main__":
    main()