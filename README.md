# wwfCheat
I got sick of losing to my grandma in words with friends 2 so I developed this to calculate the best possible words to play on my turn. Runs at about 10 words/sec so needs some optimization. Performs better at the beginning of the game as there are less anagrams to check.

Current Process

1. Calculate anagrams
2. Check which anagrams are valid words (this takes the longest => checks 10 anagrams/sec and depending on the stage of the game there can be 130k+ anagrams)
3. Calculate which valid word is worth the most points


How you can help?
- Help me come up with a better algorithm for detecting which words are flawed. < 5% of the anagrams are valid words so a majority of the run time is wasted checking words that don't work.
- Help me come up with a better way to calculate anagrams. Currently the anagrams are calculated using every letter on the table and in the users "hand". Though words can only be formed out of the letters in the rows/cols. I have not come up with an efficient way to calculate the anaagrams going by row/col instead of the whole table.
