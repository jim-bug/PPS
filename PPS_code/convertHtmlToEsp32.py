with open("html_text.txt", 'r') as file:
	for i in file:
		print(f"client.println({i.lstrip().rstrip()});")
