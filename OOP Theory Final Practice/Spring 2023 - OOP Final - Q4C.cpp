//Part C

bool operator != (const Stock& object) {
	return (symbol != object.symbol) || (companyName != object.symbol)
}

// in stock class ^