local i = io.read()
for j=1,i do
	turtle.dig()
	turtle.forward()
	turtle.digUp()
end
