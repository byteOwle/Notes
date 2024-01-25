words = open("coding_qual_input.txt", "r")

# def decode(message_file):
#     wordsList = message_file.readlines()
#     newWordList = []
#     for word in wordsList:
#         key, value = word.split()
#         newWordList.append({int(key): value})
#         # print(key, value)
#     sortedWordList = sorted(newWordList, key=lambda d: list(d.keys())[0]) 
#     print(wordsList)
#     print(sortedWordList)
#     # word = ""

#     # for i in range(1, 100):
#     #     # I need to know each edge number for each level
#     #     # Levels are unknown
#     #     edgeNumber = int((i * (i + 1)) / 2)
#     #     if edgeNumber > len(sortedWordList):
#     #         break

#     #     word = word + sortedWordList[edgeNumber-1][edgeNumber] + " "
    
#     # return word
#     return "Ehh"

def decode(message_file):
    wordsList = message_file.readlines()
    newWordList = []
    wordMap = {}
    for word in wordsList:
        key, value = word.split()
        wordMap[int(key)] = value
        # newWordList.append({int(key): value})
        # print(key, value)
    # sortedWordList = sorted(newWordList, key=lambda d: list(d.keys())[0]) 
    # print(wordMap)
    # print(sortedWordList)
    word = ""
    for i in range(1, 999):
        edgeNumber = int((i * (i + 1)) / 2)
        if edgeNumber in wordMap:
            word = word + wordMap[edgeNumber] + " "
            continue

        break
    # for i in range(1, 100):
    #     # I need to know each edge number for each level
    #     # Levels are unknown
    #     edgeNumber = int((i * (i + 1)) / 2)
    #     if edgeNumber > len(sortedWordList):
    #         break

    #     word = word + sortedWordList[edgeNumber-1][edgeNumber] + " "
    
    return word
    # return "Ehh"



print(decode(words))

