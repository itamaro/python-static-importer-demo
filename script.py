print("Hello from embedded Python!")

import dynmod

a = 10
b = 20
c = dynmod.add(a, b)
print(f"The sum is: {c}")

import staticmod

staticmod.say_hello()

print(f"{dynmod=}\n{staticmod=}")
