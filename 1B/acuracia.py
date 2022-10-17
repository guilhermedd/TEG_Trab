flowers_file = []

with open('edges.txt') as f:
     for line in f:
          flowers.append(int(x) for x in line.split(' '))
flowers.remove(flowers[0])
