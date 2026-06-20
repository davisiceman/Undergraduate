'''
Week One Assignment - Simple String Searching 
'''

'''
Given excerpt from the hacker manifesto 

Complete the script below to do the following:
1) Add your name, date, assignment number to the top of this script
2) Convert the string to all lower case
3) Count the number characters in the string
4) Count the number of words in the string
5) Sort the words in alphabetical order
6) Search the excerpt variable given below
   For the following and report how many occurances of each are found
   scandal
   arrested
   er
   good
   tomorrow
7) Submit
   NamingConvention: lastNameFirstInitial_Assignment_.ext
   for example:  alharthiD_WK1_script.py
                 alharthiD_WK1_screenshot.jpg
   A) Screenshot of the results in WingIDE
   B) Your Script
'''

excerpt = " Another one got caught today, it's all over the papers. Teenager Arrested in Computer Crime Scandal, Hacker Arrested after Bank Tampering kids. They're all alike"

''' Your work starts here '''
# Davis Iceman, January 18, 2025, Assignment #1

''' 
Week One Assignment - Simple String Searching 
'''

excerpt = " Another one got caught today, it's all over the papers. Teenager Arrested in Computer Crime Scandal, Hacker Arrested after Bank Tampering kids. They're all alike"

# Convert the string to all lower case
excerpt_lower = excerpt.lower()

# Count the number of characters in the string
char_count = len(excerpt_lower)

# Count the number of words in the string
word_count = len(excerpt_lower.split())

# Sort the words in alphabetical order
sorted_words = sorted(excerpt_lower.split())

# Search for occurrences of specific words/phrases
search_terms = ["scandal", "arrested", "er", "good", "tomorrow"]
search_results = {term: excerpt_lower.count(term) for term in search_terms}

# Print the results
print("Converted to lower case:")
print(excerpt_lower)
print()

print(f"Number of characters: {char_count}")
print(f"Number of words: {word_count}")
print()

print("Words sorted alphabetically:")
print(sorted_words)
print()

print("Search term occurrences:")
for term, count in search_results.items():
    print(f"{term}: {count}")