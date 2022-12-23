from random import randint
from random import choice 
maxElement = 100000

def arrayGenerator(n, ordered_elements, random_elements, partially_ordered_elements):
  # Generate a list of n ordered integers
  ordered_elements[:] = list(range(n))

  # Generate a list of n random integers
  random_elements[:] = [randint(0, maxElement) for _ in range(n)]

  # Generate a list of n partially ordered integers
  for i in range(n):
    if i < n / 2:
      partially_ordered_elements.append(i)
    else:
      partially_ordered_elements.append(randint(0, maxElement))
  

n = 10000

#generate tests for insert
ordered = []
random = []
partially_ordered = []
arrayGenerator(n, ordered, random, partially_ordered)

operations_insert_o = []
operations_insert_r = []
operations_insert_pr = []

operations_delete_o = []
operations_delete_r = []
operations_delete_pr = []


for i in range(len(ordered)):
  operations_insert_o.append("0 " + str(ordered[i]))       #0 is insert
  operations_insert_r.append("0 " + str(random[i]))       #0 is insert
  operations_insert_pr.append("0 " + str(partially_ordered[i]))       #0 is insert

for i in range(len(ordered)):
  operations_delete_o.append("1 " + str(choice(ordered)))       #0 is insert
  operations_delete_r.append("1 " + str(choice(random)))       #0 is insert
  operations_delete_pr.append("1 " + str(choice(partially_ordered))) 

# with open('in/test16.in', 'w') as f:
#   f.write(str(n*2) + '\n')                     
#   for item in operations_insert_o:
#     f.write(item + '\n')
#   for item in operations_delete_o:
#     f.write(item + '\n')


# with open('in/test17.in', 'w') as f:                      
#   f.write(str(n*2) + '\n')                      
#   for item in operations_insert_r:
#     f.write(item + '\n')
#   for item in operations_delete_r:
#     f.write(item + '\n')

# with open('in/test18.in', 'w') as f:                      
#   f.write(str(n*2) + '\n')                      
#   for item in operations_insert_pr:
#     f.write(item + '\n')
#   for item in operations_delete_pr:
#     f.write(item + '\n')


complex_test = []
random_elements = []
random_elements[:] = [randint(0, maxElement) for _ in range(n)]
for i in range(n): 
  command = randint(0, 4)
  if command == 0:
    complex_test.append("0 " + str(choice(random_elements)))

  if command == 1:
    complex_test.append("1 " + str(choice(random_elements)))
    pass
  if command == 2:
    complex_test.append("2 " + str(choice(random_elements)))
    pass
  if command == 3:
    complex_test.append("3 " + str(choice(random_elements))+ " " + str(randint(0, maxElement)))
    pass
  if command == 4:
    complex_test.append("4")
    pass
  
with open('in/test21.in', 'w') as f:
  f.write(str(n) + '\n')                     
  for item in complex_test:
    f.write(item + '\n')