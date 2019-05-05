import re

class Kwic:

    def __init__(self, excluded, lines):
        self.excluded = excluded
        self.index_lines = lines
        self.keyWords = self. extractKeyWords(excluded, lines)
        
    def extractKeyWords(self, excluded, lines):
         sentence = []
         indexWord = []
         temp = []
         x = 0
         ifKeyWord = 0
         for line in lines:
              sentence.append(line)
              sentence = [x.strip() for x in sentence]
              temp = line.strip().split(" ") #split line with space
              for words in temp: #check every single words in temp
                   ifKeyWord = 0; #set boolean value to 0
                   for x in range(0, len(excluded)): #go through every words in excluded
                        if(words.lower() == excluded[x]): #if one word is matched
                             if words != " ":
                                 ifKeyWord = 1; #set the boolean value to one
                   if(ifKeyWord == 0): #only with boolean value 1, can be append to the list
                        indexWord.append(words)
         return indexWord #return a list of index word unsorted
           
    def sortWords(self, keyWords): #sort all the words, number first, then letter
         for i in range(len(keyWords)-1,0,-1):
            for j in range(i):
                 if keyWords[j].lower() > keyWords[j+1].lower():
                      temp = keyWords[j]
                      keyWords[j] = keyWords[j+1]
                      keyWords[j+1] = temp
    
    
    def capitalization(self,target, lines):
         outputLines = lines.split(" ")
         count = 0
         for words in outputLines:
              if words == target:
                   outputLines[count] = words.upper()
                   break
              count += 1
         outputLines = " ".join(outputLines)
         m = re.search(r'(.*)\b(%s\b(.*))' % target.upper(), outputLines, flags=0) #search for the target word and split the string into two parts
         front = m.group(1)
         back = m.group(2)
         while len(front) > 20: #pop the first word if the string is longer than 20
              front = front.split(" ")
              front.pop(0)
              front = " ".join(front)
         while len(back) > 31: #pop the last word if the string is longer than 30
              back = back.split(" ")
              back.pop()
              back = " ".join(back)
         spaceRange = 20 -1 - len(front) #the space area required in the front
         spaceArea = []
         for i in range(0 , spaceRange + 10):
              spaceArea.append(" ") #append space to the list
         spaceArea = "".join(spaceArea) #join the spaceArea as a string
         output = spaceArea + front + back #combime space front and back together
         return output
      
    def output(self):
         x = 0
         self.sortWords(self.keyWords)
         contentIndex = []
         for line in self.index_lines: #created an index matched for the position for every single words
             contentIndex.append([])
             for words in line.split(" "):
                  contentIndex[x].append(0) #set the index to 0
             x += 1
         printOut = []
         w = 0
         for words in self.keyWords:
              y = 0
              isIndexed = 0 #set a boolean value of if the word is indexed to 0
              for line in self.index_lines:
                   if isIndexed == 0:
                       z = 0
                       for passWords in line.split(" "): #go through every single words in the line
                            if isIndexed == 0:
                                 if passWords == words and contentIndex[y][z] != 1: #the words must match key word and its index must be 0
                                      self. printText = self.capitalization(words, line)
                                      printOut.append(self.printText)
                                      isIndexed = 1 #set the boolean value for this word to one to prevent the loop further going on
                                      contentIndex[y][z] = 1 #set the boolean value matched this position to 1
                                 z += 1
                       y += 1
         return printOut


