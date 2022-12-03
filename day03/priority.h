int priority(char item) {
	return (item - (item >= 'a' ? 'a' : 'A')) + (item >= 'a' ? 1 : 27);
}