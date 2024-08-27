from sys import argv

with open(argv[0], 'r') as file:		# use python3 convertHtmlToEsp32 <name>.txt
	for i in file:
		print(f"client.println(\"{i.lstrip().rstrip().replace("\"", "\\\"")}\");")
