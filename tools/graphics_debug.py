from subprocess import call
import sys
import shutil
import getopt
import os.path

# This script starts a graphics trace with apitrace, 
# and when done the gui is opened with that trace file.

def main():
	#dir = os.path.dirname(os.path.abspath(__file__))
	#os.chdir(dir + "../")

	arc = "x86"
	debug = "Release"
	outputName = "MinionGraphics.trace"
	filename = "MinionGraphics_x86_d.exe"
	apitraceDir = "D:/apitrace/x86/bin/" 
	try:
		opts, args = getopt.getopt(sys.argv[1:], "drf:o:x:", ["x64", "x86", "debug", "file="])
		
	except getopt.GetoptError as err:
		print(err)
		return
		
	for	opt, arg in opts:
		if(opt == "-a"):
			arc = arg
		elif opt == "-d":
			debug = "Debug"
		elif opt == "-r":
			debug = "Release"
		elif opt == "-f":
			filename = arg
		elif opt == "--x86":
			arc = "x86"
			apitraceDir = "D:/apitrace/x86/bin/"
		elif opt == "--x64":
			arc = "x64"
			apitraceDir = "D:/apitrace/x64/bin/"
		elif opt == "-x":
			if arg == "-x86" or arg == "-x64":
				arc = "x" + arg
				apitraceDir = "D:/apitrace/x" + arg + "/bin/"
		elif opt == "-o":
			outputName = arg
	
	f = "../output/MinionGraphics/" + arc + "/" + debug + "/" + filename
	f = filename
	output = "../output/MinionGraphics/" + arc + "/" + debug + "/" + outputName
	
	final = apitraceDir + "apitrace.exe trace --api gl " + f + " --output " + output
	#print (final)
	
	if os.path.isfile(outputName) == True:
		os.remove(outputName)

	call(final)
	
	call(apitraceDir + "apitrace " + outputName)
	
if __name__ == "__main__":
    main()
	
	