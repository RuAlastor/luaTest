function createTables()
        local tableAmount = 4
	local tableOfTables = {}

	for i = 1, tableAmount do
		tableOfTables[i] = {}
                local endJ = 5
		for j = 1, endJ do
                        tableOfTables[i][j] = j
			io.write(tableOfTables[i][j], " ")
		end
		print()
	end
	return tableOfTables
end


