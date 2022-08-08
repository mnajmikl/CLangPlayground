Progressbar
This is a C language rewrite from a simple code I wrote in Python. Demonstrate progress text / bar (command line application)

The original Python code
for i in range(120,24001): progress = i total = 24000 percent = 100 * (progress/total) bar = '*' * int(percent) + '-' * (100 - int(percent)) print(f"\r|{bar}| {percent:.2f}%", end="\r")

The rewrite requires a function to repeat a string/char and a function for formatted progress output.
