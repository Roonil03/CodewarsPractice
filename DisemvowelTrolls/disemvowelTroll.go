package kata

func Disemvowel(comment string) string {
	res := []rune{}
	for _, ch := range comment {
		switch ch {
		case 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U':
			continue
		default:
			res = append(res, ch)
		}
	}
	return string(res)
}
