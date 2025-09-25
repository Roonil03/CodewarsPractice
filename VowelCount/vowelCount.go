package kata

func GetCount(str string) (count int) {
	// Enter solution here
	for _, ch := range str {
		switch ch {
		case 'a', 'e', 'i', 'o', 'u':
			count++
		}
	}
	return count
}
