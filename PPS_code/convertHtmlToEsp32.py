"""
 Author: Ignazio Leonardo Calogero Sperandeo
 Date: 25/08/2024
 Project Name: PPSv2
 Repo: https://github.com/jim-bug/PPS/tree/pps-v2

 by jim_bug // :)
"""

from sys import argv

with open(argv[0], 'r') as file:		# use python3 convertHtmlToEsp32 <name>.txt
	for i in file:
		print(f"client.println(\"{i.lstrip().rstrip().replace("\"", "\\\"")}\");")
// :)

