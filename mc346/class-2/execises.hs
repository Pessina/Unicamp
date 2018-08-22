
pos element l = pos' element l 1 where
                     pos' element [] acc = []
                     pos' element (x:xs) acc = if x == element
                     then acc:pos' element xs (acc+1)
                     else pos' element xs (acc+1)
