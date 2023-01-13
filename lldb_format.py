import sys
import lldb

def __lldb_init_module(debugger, dict):
    #utl::vector
    debugger.HandleCommand('type summary add -x utl::vector< --summary-string "Size: ${var.__data_.size}" -w utl')
    debugger.HandleCommand('type synthetic add -x "utl::vector<" --python-class lldb_format.VectorElementsProvider -w utl')
    debugger.HandleCommand('type summary add -x utl::small_vector< --summary-string "Size: ${var.__data_.size}" -w utl')
    debugger.HandleCommand('type synthetic add -x "utl::small_vector<" --python-class lldb_format.VectorElementsProvider -w utl')
    
    #utl::ilist
    debugger.HandleCommand('type synthetic add -x "utl::ilist<" --python-class lldb_format.IListElementsProvider -w utl')

class VectorElementsProvider:
    def __init__(self, valobj, internalDict):
        self.valueObject = valobj
        self.size = self.valueObject.GetChildMemberWithName('__data_').GetChildMemberWithName('size').GetValueAsUnsigned()
        
    def num_children(self):
        return min(self.size, 999)

    def get_child_index(self, name):
        return int(name.lstrip('[').rstrip(']'))
        
    def get_child_at_index(self, index):
        if index == 0 and self.inline:
            return self.data_ptr.CreateValueFromExpression('[??]', '.')
        offset = index * self.data_size - self.inline
        return self.data_ptr.CreateChildAtOffset("[{:>3}]".format(index), offset, self.data_type)
     
    def update(self):
        self.data_ptr  = self.valueObject.GetChildMemberWithName('__data_').GetChildMemberWithName('begin_inline').GetChildMemberWithName('_p')
        self.inline    = self.data_ptr.GetData().uint64[0] % 2
        self.data_type = self.valueObject.GetType().GetTemplateArgumentType(0)
        self.data_size = self.data_type.GetByteSize()

class IListElementsProvider:
    def __init__(self, valobj, internalDict):
        self.valueObject = valobj
        self.size = self.compute_size()
                
    def num_children(self):
        return self.size

    def get_child_index(self, name):
        return int(name.lstrip('[').rstrip(']'))
        
    def get_child_at_index(self, index):
        if index == 0:
            self.itr = self.sent.GetChildMemberWithName('__next')
        else:
            self.itr = self.itr.GetChildMemberWithName('__next')
        return self.itr.CreateChildAtOffset('[' + str(index) + ']', 0, self.data_type)
     
    def update(self):
        self.sent  = self.valueObject.GetChildMemberWithName('__sentinel_')
        self.data_type = self.valueObject.GetType().GetTemplateArgumentType(0)
        self.data_size = self.data_type.GetByteSize()

    def compute_size(self):
        sent  = self.valueObject.GetChildMemberWithName('__sentinel_')
        sent_addr = sent.AddressOf().GetData().uint64[0]
        i = sent.GetChildMemberWithName('__next')
        k = 0
        while k < 100: # To be safe
            i_data = i.GetData().uint64[0]
            if i_data == sent_addr:
                break
            i = i.GetChildMemberWithName('__next')
            k += 1
        return k
