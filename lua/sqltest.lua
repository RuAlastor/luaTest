package.cpath = "/usr/lib/x86_64-linux-gnu/liblua5.3-sql-postgres.so;/usr/lib/liblua5.3.so;"

function getUser(lname)
        local driver = require "luasql.postgres"
        local env = assert(driver.postgres())

        local con = assert(env:connect("luabase", "sorokin", "123456", "127.0.0.1", "5432"))
        --                              database   user       pwd       ip           port

        --res = con:execute("DROP TABLE users")

        --res = assert(con:execute("CREATE TABLE users( \
        --                                                id INTEGER PRIMARY KEY, \
        --                                                fname TEXT, \
        --                                                lname TEXT, \
        --                                                job TEXT \
        --                                             )"
        --                         ))

        --res = assert(con:execute("INSERT INTO users(id, fname, lname, job) \
        --                          VALUES (1, 'Andrey', 'Sedin', 'Deputat')"
        --                         ))
        --res = assert(con:execute("INSERT INTO users \
        --                          VALUES (2, 'Andrey', 'Dranga', 'Boxer')"
        --                         ))
        --res = assert(con:execute("INSERT INTO users \
        --                          VALUES (3, 'Roberto', 'Ierusalimskiy', 'Programmer')"
        --                         ))



        local cursor = assert(con:execute("SELECT * FROM users WHERE lname = '" .. lname .. "'"))

        --print()
        print(string.format("%1s %-16s %-16s %-16s",
                        "#", "| FNAME", "| LNAME", "| JOB"))
        print(string.format("%1s %-16s %-16s %-16s",
			"-", "| -----", "| -----", "| ---"))

        local row = cursor:fetch({}, "a")
        --print(string.format("%1s %1s %-15s%1s %-15s%1s %-15s",
        --                row.id, "|", row.fname, "|", row.lname, "|", row.job))
        --print()

	cursor:close()
        con:close()
	env:close()

        return row
        --return row.id, row.fname, row.lname, row.job
end
