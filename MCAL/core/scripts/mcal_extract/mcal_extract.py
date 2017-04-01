import os, shutil
import sys
import optparse
import config
from difflib import unified_diff
from os.path import abspath, dirname, join, isdir

is_verbose = False
suppress_warnings = False

def verbose_print(arg):
	if is_verbose:
		print( arg )

def print_diff(from_file, to_file):
	from_f = open(from_file)
	from_lines = from_f.readlines()
	from_f.close()
	to_f = open(to_file)
	to_lines = to_f.readlines()
	to_f.close()
	difflines = unified_diff(from_lines, to_lines, fromfile=from_file, tofile=to_file)
	num_diffs = 0
	for line in difflines:
		sys.stdout.write(line)
		num_diffs = num_diffs + 1
	if num_diffs == 0:
		print "Files are identical"

def extract_mcal(mcal_target_dir, core_base_dir,mapping_name, suppress_diffs):
		print "SETTINGS:"
		print "mapping_name = " + mapping_name
		print "mcal_target_dir = " + mcal_target_dir
		print "core_base_dir = " + core_base_dir
		print ""

		try:
			exec("from %s import *" % mapping_name)
		except :
			print("Mapping location does not exist or is not a proper python module")
		else:
			pass

		# moddefs, yaml, chk, generator implementations.arxml

		print "LOG:"

		numberOfFiles = 0

		for module_name, module_mapping in file_mappings.iteritems():
			verbose_print( "Module: " + module_name.capitalize() )
			for from_file, to_file in module_mapping.iteritems():
				verbose_print( abspath( join( core_base_dir,from_file) ) + " => " + abspath( join( mcal_target_dir,to_file ) ) )
				if not isdir( abspath( dirname( join( mcal_target_dir,to_file ) ) ) ):
					print "Creating dir: " + abspath( dirname( join( mcal_target_dir,to_file ) ) )
					os.makedirs( abspath( dirname( join( mcal_target_dir,to_file ) ) ) )
				shutil.copyfile( join( core_base_dir,from_file), join( mcal_target_dir,to_file ) )
				numberOfFiles = numberOfFiles + 1

		for module_name, module_mapping in patch_file_mappings.iteritems():
			verbose_print( "Module: " + module_name.capitalize() )
			for from_file, to_file in module_mapping.iteritems():
				from_file_path = join( "./core/scripts/mcal_extract/" + mapping_name.split(".")[0],from_file)
				print( "WARNING: File is replaced: " + abspath( from_file_path ) + " => " + abspath( join( mcal_target_dir,to_file ) ) )
				if not isdir( abspath( dirname( join( mcal_target_dir,to_file ) ) ) ):
					print "Creating dir: " + abspath( dirname( join( mcal_target_dir,to_file ) ) )
					os.makedirs( abspath( dirname( join( mcal_target_dir,to_file ) ) ) )
				if not suppress_diffs:
					print_diff( join( mcal_target_dir,to_file ), from_file_path )
				shutil.copyfile( from_file_path, join( mcal_target_dir,to_file ) )
		print ""
		
		print "DONE:"
		print str(numberOfFiles) + " files copied."

if __name__ == "__main__":

	#from mpc5645s_plain.mpc5645s_plain import *

	parser = optparse.OptionParser()
	parser.add_option("-m", "--mapping_name", dest = "mapping_name", help="Name of mapping. <rel_path>.<py_file_name> (folder needs to include \"__init__.py\")")
	parser.add_option("-s", "--suppress_diffs", action="store_true", dest = "suppress_diffs", help="Don't output diffs for replaced files")
	parser.add_option("-v", "--verbose",action="store_true", dest="verbose")
	(options, args) = parser.parse_args()

	is_verbose = options.verbose
	suppress_diffs = options.suppress_diffs

	mcal_target_dir = config.DEFAULT_MCAL_TARGET_DIR
	core_base_dir = config.DEFAULT_CORE_BASE_DIR

	options.mapping_name = options.mapping_name or config.DEFAULT_MAPPING_NAME

	extract_mcal(mcal_target_dir, core_base_dir, options.mapping_name, suppress_diffs)
