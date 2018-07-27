# Bootstraping

## Prepare 
- determine ip address of raspberry, e.g. inspect dhcp logfile
- enter ip in `hosts` file - in section newhosts

        [newhosts]
        the.ip.of.new.raspi
        
        [prebootstrap]
        


- (optional) update sshkey file

        :::sh
        ssh-keygen -t rsa -b 4096 -C "IoT master node" -f files/iot_master

## Run bootstrap playbook

- run playbook for new hosts - phase 1

        :::sh
        ansible-playbook bootstrap.yml -i hosts --ask-pass
        

- move ip of raspi to prebootstrap section in `hosts` file

        [newhosts]
        
        [prebootstrap]
        the.ip.of.new.raspi
        

- run playbook for prepared hosts - phase 2


After running both phases 
- ssh access is restricted to authorized key 
- ssh password authentication is disabled
- pi password is set to 'tq2018' - to install another password modify `pi_password_hash` in `group_vars/all.yml`

# Run specific playbooks